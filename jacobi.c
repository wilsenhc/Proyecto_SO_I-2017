/**
 * Universidad de Carabobo
 * Facultad de Ciencias y Tecnología
 * Sistemas Operativos
 * Proyecto Semestre I-2017
 *
 * Freddy Duran
 * Michele Sanseviero
 * Wilsen Hernández
 * */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

struct {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double **matrizA;
    double *vectorB, *vectorX, *vectorXInicial;
} JACOBI;

struct Intervalo {
    int min;
    int max;
};

int NUM_THREADS;
int *intervalos;
pthread_t *THREADS_ARR;

/**
 * Lectura de archivo de entrada
 * */
void lecturaJacobi()
{
    scanf(" %d", &JACOBI.dimensionMatriz);

    JACOBI.matrizA = (double**) calloc(JACOBI.dimensionMatriz, sizeof(double*));

    for (int i = 0; i < JACOBI.dimensionMatriz; i++)
    {
        JACOBI.matrizA[i] = (double*) calloc(JACOBI.dimensionMatriz, sizeof(double));
    }

    JACOBI.vectorB = (double*) calloc(JACOBI.dimensionMatriz, sizeof(double));
    JACOBI.vectorX = (double*) calloc(JACOBI.dimensionMatriz, sizeof(double));
    JACOBI.vectorXInicial = (double*) calloc(JACOBI.dimensionMatriz, sizeof(double));
    for(int i = 0; i < JACOBI.dimensionMatriz;i++)
    {
        JACOBI.vectorB[i] = 0;
        JACOBI.vectorX[i] = 0;
        JACOBI.vectorXInicial[i] = 0;
        for(int j = 0;j < JACOBI.dimensionMatriz ; j++)
        {
            JACOBI.matrizA[i][j] = 0;
        }
    }

    scanf(" %lf", &JACOBI.tolerancia);
    scanf(" %d", &JACOBI.maximoIteraciones);

    for (int i = 0; i < JACOBI.dimensionMatriz; i++)
    {
        scanf(" %lf", &JACOBI.vectorXInicial[i]);
    }

    for (int i = 0; i < JACOBI.dimensionMatriz; i++)
    {
        for (int j = 0; j < JACOBI.dimensionMatriz; j++)
        {
            scanf(" %lf", &JACOBI.matrizA[i][j]);
        }
    }

    for (int i = 0; i < JACOBI.dimensionMatriz; i++)
    {
        scanf(" %lf", &JACOBI.vectorB[i]);
    }

    intervalos = (int *) calloc(NUM_THREADS + 1, sizeof(int));
    intervalos[0] = 0;
    intervalos[NUM_THREADS] = JACOBI.dimensionMatriz;

    for(int i = 1; i < NUM_THREADS; i++)
    {
        intervalos[i] = i * (JACOBI.dimensionMatriz / NUM_THREADS);
    }
}

/**
 * Calcular la distancia entre el vector de Xi y XOi
 * */
double normaVector()
{
    double sum = 0e0;
    for (int i = 0; i < JACOBI.dimensionMatriz; i++)
    {
        sum = sum + pow(JACOBI.vectorX[i] - JACOBI.vectorXInicial[i], 2);
    }

    return sqrt(sum);
}

double sumatoria(int i)
{
    double total = 0e0;

    for (int j = 0; j < JACOBI.dimensionMatriz; j++)
    {
        if (j != i)
        {
            total = total + (JACOBI.matrizA[i][j] * JACOBI.vectorXInicial[j]);
        }
    }
    return total;
}

void *operacion(void *F)
{
    struct Intervalo *i = (struct Intervalo*) F;

    for(int j = i->min; j < i->max;j++)
    {
        JACOBI.vectorX[j] = (1 / JACOBI.matrizA[j][j]) * (-1 * sumatoria(j) + JACOBI.vectorB[j]);
    }
    pthread_exit(0);
}

void instanciar_hilos()
{
    int *distancia;
    int delta;

    THREADS_ARR = (pthread_t *) calloc(NUM_THREADS, sizeof(pthread_t));

    if(THREADS_ARR == NULL)
    {
        printf("Se jodio el hilo");
    }
    else
    {
        for(int i = 0; i < NUM_THREADS; i++)
        {
            struct Intervalo intervals;
            intervals.min = intervalos[i];
            intervals.max = intervalos[i + 1];

            pthread_create(&THREADS_ARR[i], NULL, operacion, &intervals);
            pthread_join(THREADS_ARR[i], NULL);
        }
        free(THREADS_ARR);
    }
}

/**
 * Algoritmo 7.1 de Numerical Analysis por Burden & Faires
 * */
void jacobiIterativo()
{

    int band = 0;
    int k = 0;

    while (k < JACOBI.maximoIteraciones)
    {
        if(NUM_THREADS > 1)
        {
            instanciar_hilos();
        }
        else
        {
            for (int i = 0; i < JACOBI.dimensionMatriz; i++)
            {
                JACOBI.vectorX[i] = (1 / JACOBI.matrizA[i][i]) * (-1 * sumatoria(i) + JACOBI.vectorB[i]);
            }
        }

        if (normaVector() < JACOBI.tolerancia)
        {
            break;
        }

        for(int j = 0; j < JACOBI.dimensionMatriz; j++)
        {
            JACOBI.vectorXInicial[j] = JACOBI.vectorX[j];
        }

        k++;
    }

    if (k <= JACOBI.maximoIteraciones && !band)
    {
        printf("Solucion encontrada en %d iteraciones\n", k);
    }
    else
    {
        printf("Se excedio de el numero de iteraciones\n");
    }
}

void liberarMemoria()
{
    for(int i = 0; i < JACOBI.dimensionMatriz ; i++)
    {
        free(JACOBI.matrizA[i]);
    }

    free(JACOBI.vectorB);
    free(JACOBI.vectorX);
    free(JACOBI.vectorXInicial);
    free(JACOBI.matrizA);
    free(intervalos);
}

int main(int argc, char** argv)
{
    struct timeval t, t2;
    double microsegundos = 0e0;

    /**
     * Verificar si se especifica una cantidad de hilos,
     * sino resolver utilizando un solo hilo
     * */
    if (argc > 1) {
        NUM_THREADS = atoi(argv[1]);
    } else {
        NUM_THREADS = 1;
    }

    lecturaJacobi();

    gettimeofday(&t, NULL);
    jacobiIterativo();
    gettimeofday(&t2, NULL);
    microsegundos = ((t2.tv_usec - t.tv_usec)  + ((t2.tv_sec - t.tv_sec) * 1000000.0f));
    printf("\nEl tiempo con %d hilos fue de %lf microsegundos\n", NUM_THREADS, microsegundos);
    return 0;
}