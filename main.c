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

void jacobiIterativo()
{
    int band = 0;
    int k = 0;

    while (k < JACOBI.maximoIteraciones)
    {
        for (int i = 0; i < JACOBI.dimensionMatriz; i++)
        {
            JACOBI.vectorX[i] = (1 / JACOBI.matrizA[i][i]) * (-1 * sumatoria(i) + JACOBI.vectorB[i]);
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

double normaVector()
{
    double sum = 0e0;
    for (int i = 0; i < JACOBI.dimensionMatriz; i++)
    {
        sum = sum + pow(JACOBI.vectorX[i] - JACOBI.vectorXInicial[i], 2);
    }

    return sqrt(sum);
}

int main(int argc, char** argv)
{

    lecturaJacobi();


    jacobiIterativo();

    return 0;
}