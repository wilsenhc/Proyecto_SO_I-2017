/**
 * Universidad de Carabobo
 * Facultad de Ciencias y Tecnología
 * Sistemas Operativos
 * Proyecto Semestre I-2017
 *
 * Freddy Duran
 * Michelle Sanseviero
 * Wilsen Hernández
 * */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double **matrizA;
    double *vectorB, *vectorX, *vectorXInicial;
} Jacobi;

int main(int argc, char** argv)
{
    Jacobi jacobi;

    /**
     * Lectura de archivo de entrada
     * */
    scanf(" %d", &jacobi.dimensionMatriz);

    jacobi.matrizA = (double**) calloc(jacobi.dimensionMatriz, sizeof(double*));

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        jacobi.matrizA[i] = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
    }

    jacobi.vectorB = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
    jacobi.vectorX = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
    jacobi.vectorXInicial = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));

    scanf(" %lf", &jacobi.tolerancia);
    scanf(" %d", &jacobi.maximoIteraciones);

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        scanf(" %lf", &jacobi.vectorXInicial[i]);
    }

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        for (int j = 0; j < jacobi.dimensionMatriz; j++)
        {
            scanf(" %lf", &jacobi.matrizA[i][j]);
        }
    }

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        scanf(" %lf", &jacobi.vectorB[i]);
    }

    return 0;
}