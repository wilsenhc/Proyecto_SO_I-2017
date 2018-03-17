/**
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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <math.h>
#define N 4
=======
>>>>>>> f2d3ea31f5169bab118d560c371008ebd3ef6a3e

typedef struct {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double matrizA[N][N];
    double vectorB[N], vectorX[N], vectorXInicial[N];
} Jacobi;

void jacobiIterativo(Jacobi J);
double sumatoria(Jacobi J,int i);
double normaVector(Jacobi J);

int main(int argc, char** argv)
{
    Jacobi jacobi;

    /**
     * Lectura de archivo de entrada
     * */
    scanf(" %d", &jacobi.dimensionMatriz);

    //jacobi.matrizA = (double**) calloc(jacobi.dimensionMatriz, sizeof(double*));

    //for (int i = 0; i < jacobi.dimensionMatriz; i++)
    {
    //    jacobi.matrizA[i] = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
    }

   /* jacobi.vectorB = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
    jacobi.vectorX = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
    jacobi.vectorXInicial = (double*) calloc(jacobi.dimensionMatriz, sizeof(double));
*/
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

    jacobiIterativo(jacobi);

    return 0;
}

void jacobiIterativo(Jacobi J)
{
    int band = 0;
    int k = 0;

    while (k < J.maximoIteraciones)
    {
        for(int i = 0; i < J.dimensionMatriz;i++)
        {
            J.vectorX[i] = (1 / J.matrizA[i][i]) * (-1 * sumatoria(J,i) + J.vectorB[i]);
        }

        if (normaVector(J) < J.tolerancia)
        {
            break;
        }

        for(int j = 0; j < J.dimensionMatriz; j++)
        {
            J.vectorXInicial[j] = J.vectorX[j];
        }

        printf("%2d", k);

        for (int j = 0; j < J.dimensionMatriz; j++)
        {
            printf(" %f", J.vectorX[j]);
        }
        printf("\n");

        k++;
    }

    if (k <= J.maximoIteraciones)
    {
        printf("Solucion encontrada en %d iteraciones\n", k);
    }
    else
    {
        printf("Se excedio de el numero de iteraciones\n");
    }

}


double sumatoria(Jacobi J, int i)
{
    double total = 0e0;

    for (int j = 0; j < J.maximoIteraciones; j++)
    {
        if (j != i)
        {
            total = total + (J.matrizA[i][j] * J.vectorXInicial[j]);
        }
    }
    return total;
}

double normaVector(Jacobi J)
{
    double sum = 0e0;
    for (int i = 0; i < J.dimensionMatriz; i++)
    {
        sum = sum + pow(J.vectorX[i] - J.vectorXInicial[i], 2);
    }

    return sqrt(sum);
}