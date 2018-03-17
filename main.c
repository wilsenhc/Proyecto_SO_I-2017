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

struct {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double **matrizA;
    double *vectorB, *vectorX, *vectorXInicial;
} JACOBI;

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
}
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

    for (int j = 0; j < JACOBI.maximoIteraciones; j++)
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
    int *i = (int*)F;

    for(int j = i[0]; j < i[1];j++)
    {
        JACOBI.vectorX[j] = (1 / JACOBI.matrizA[j][j]) * (-1 * sumatoria(j) + JACOBI.vectorB[j]);
    }
}

void crear_hilos(int hilo)
{
    int *distancia;
    int i,aux,V[2];
    pthread_t *H;//Vector de Hilos

    distancia = (int*)calloc(hilo+1,sizeof(int));
    H = (pthread_t*)calloc(hilo,sizeof(pthread_t));
    if(H == NULL)
    {
        printf("Se jodio el hilo");
    }
    else
    {
        aux = JACOBI.dimensionMatriz/hilo;
        distancia[0] = 0;
        for(i = 1; i < hilo;i++)
        {
            distancia[i] = distancia[i-1] + aux;
        }
        distancia[hilo] = JACOBI.dimensionMatriz;
        for(i = 0;i < hilo;i++)
        {
            V[0] = distancia[i];
            V[1] = distancia[i+1];
            pthread_create(&H[i], NULL, operacion, V);
            pthread_join(H[i],NULL);
        }
    }
}

void jacobiIterativo(int hilo)
{
    int band = 0;
    int k = 0;

    while (k < JACOBI.maximoIteraciones)
    {
        if(hilo > 1)
        {
            crear_hilos(hilo);
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

        printf("%2d", k);

        for (int j = 0; j < JACOBI.dimensionMatriz; j++)
        {
            printf(" %f", JACOBI.vectorX[j]);
        }
        printf("\n");

        k++;
    }

    if (k <= JACOBI.maximoIteraciones)
    {
        printf("Solucion encontrada en %d iteraciones\n", k);
    }
    else
    {
        printf("Se excedio de el numero de iteraciones\n");
    }

}

int main(int argc, char** argv)
{
    int hilo = 2;
    lecturaJacobi();


    jacobiIterativo(hilo);

    return 0;
}