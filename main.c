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

struct Jacobi {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double **matrizA;
    double *vectorB, *vectorX, *vectorXInicial;
};

int main(int argc, char** argv)
{
    Jacobi jacobi;

    /**
     * Lectura de archivo de entrada
     * */
    scanf(" %d", &jacobi.dimensionMatriz);

    jacobi.matrizA = (double*) calloc(jacobi.dimensionMatriz, sizeof(double*));

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        jacobi.matrizA[i] = (double) calloc(jacobi.dimensionMatriz, sizeof(double));
    }

    jacobi.vectorB = (double) calloc(jacobi.dimensionMatriz, sizeof(double));
    jacobi.vectorX = (double) calloc(jacobi.dimensionMatriz, sizeof(double));
    jacobi.vectorXInicial = (double) calloc(jacobi.dimensionMatriz, sizeof(double));

    scanf(" %f", &jacobi.tolerancia);
    scanf(" %d", &jacobi.maximoIteraciones);

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        scanf(" %f", &jacobi.vectorXInicial[i]);
    }

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        for (int j = 0; j < jacobi.dimensionMatriz; j++)
        {
            scanf(" %f", &jacobi.matrizA[i][j]);
        }
    }

    for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
        scanf(" %f", &jacobi.vectorB[i]);
    }

    return 0;
}