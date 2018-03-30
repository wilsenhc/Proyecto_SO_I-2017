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
struct Intervalo *intervalos;
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

    intervalos = (struct Intervalo *) calloc(NUM_THREADS, sizeof(struct Intervalo));
    intervalos[0].min = 0;
    intervalos[NUM_THREADS].max = JACOBI.dimensionMatriz;

    for(int i = 0; i < NUM_THREADS; i++)
    {
        intervalos[i].max = (i+1) * (JACOBI.dimensionMatriz / NUM_THREADS);
        intervalos[i + 1].min = (i+1) * (JACOBI.dimensionMatriz / NUM_THREADS);
    }

    THREADS_ARR = (pthread_t *) calloc(NUM_THREADS, sizeof(pthread_t));
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

void *pasoTres(void *args)
{
    struct Intervalo *intervalo = (struct Intervalo *) args;

    for(int j = intervalo->min; j < intervalo->max; j++)
    {
        JACOBI.vectorX[j] = (1 / JACOBI.matrizA[j][j]) * (-1 * sumatoria(j) + JACOBI.vectorB[j]);
    }
    pthread_exit(0);
}

void *pasoSeis(void *args)
{
    struct Intervalo *intervalo = (struct Intervalo *) args;

    for(int j = intervalo->min; j < intervalo->max; j++)
    {
        JACOBI.vectorXInicial[j] = JACOBI.vectorX[j];
    }
}

void pasoTresConHilos()
{
    if(THREADS_ARR != NULL)
    {
        for(int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&THREADS_ARR[i], NULL, pasoTres, &intervalos[i]);
        }

        for(int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(THREADS_ARR[i], NULL);
        }
    }
}

void pasoSeisConHilos()
{
    if (THREADS_ARR != NULL)
    {
        for(int i = 0; i < NUM_THREADS; i++)
        {
            pthread_create(&THREADS_ARR[i], NULL, pasoSeis, &intervalos[i]);
        }

        for(int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(THREADS_ARR[i], NULL);
        }
    }
}

/**
 * Algoritmo 7.1 de Numerical Analysis por Burden & Faires
 * */
void jacobi()
{
    // PASO #1
    int k = 0;

    // PASO #2
    while (k < JACOBI.maximoIteraciones)
    {
        // PASO #3
        if(NUM_THREADS > 1)
        {
            pasoTresConHilos();
        }
        else
        {
            for (int i = 0; i < JACOBI.dimensionMatriz; i++)
            {
                JACOBI.vectorX[i] = (1 / JACOBI.matrizA[i][i]) * (-1 * sumatoria(i) + JACOBI.vectorB[i]);
            }
        }

        // PASO #4
        if (normaVector() < JACOBI.tolerancia)
        {
            printf("La solución para una tolerancia de %lf se obtuvo exitosamente en %d iteraciones.", JACOBI.tolerancia, k + 1);
            break;
        }

        // PASO #5
        k++;

        // PASO #6
        if (NUM_THREADS > 1)
        {
            pasoSeisConHilos();
        }
        else
        {
            for(int j = 0; j < JACOBI.dimensionMatriz; j++)
            {
                JACOBI.vectorXInicial[j] = JACOBI.vectorX[j];
            }
        }

    }

    // PASO #7
    if (k >= JACOBI.maximoIteraciones)
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

    free(JACOBI.matrizA);
    free(JACOBI.vectorB);
    free(JACOBI.vectorX);
    free(JACOBI.vectorXInicial);
    free(intervalos);
    free(THREADS_ARR);
}

int main(int argc, char** argv)
{
    #ifdef DEBUG
        struct timeval t1, t2, t3;
        double ejecucion = 0e0;
        double lectura = 0e0;
        double total = 0e0;
    #endif

    /**
     * Verificar si se especifica una cantidad de hilos,
     * sino resolver utilizando un solo hilo
     * */
    if (argc > 1) {
        NUM_THREADS = atoi(argv[1]);
    } else {
        NUM_THREADS = 1;
    }

    #ifdef DEBUG
        printf("==== Con %d hilo(s) ====\n", NUM_THREADS);
        gettimeofday(&t1, NULL);
    #endif

    lecturaJacobi();

    #ifdef DEBUG
        gettimeofday(&t2, NULL);
    #endif

    jacobi();

    #ifdef DEBUG
        gettimeofday(&t3, NULL);
        lectura = ((t2.tv_usec - t1.tv_usec) + ((t2.tv_sec - t1.tv_sec) * 1e6));
        ejecucion = ((t3.tv_usec - t2.tv_usec) + ((t3.tv_sec - t2.tv_sec) * 1e6));
        total = ((t3.tv_usec - t1.tv_usec) + ((t3.tv_sec - t1.tv_sec) * 1e6));
        printf("EL tiempo de lectura fue de\t%lf segundos\n", lectura/1e6);
        printf("El tiempo de jacobi fue de\t%lf segundos\n", ejecucion/1e6);
        printf("EL tiempo de total fue de\t%lf segundos\n\n", total/1e6);
    #endif

    return 0;
}