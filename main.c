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

typedef struct {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double **matrizA;
    double *vectorB, *vectorX, *vectorXInicial;
} Jacobi;


void matriz_sup(int **matrz, int **matrz_sup, int N);
void matriz_inf(int **matrz,int **matrz_inf,int N);
void matriz_diag(int **matrz,int **matrz_diag,int N);
void inicializar_matr(int **matriz,int N);

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

//matrz = matriz original, matrz_sup = matriz con solo la triangular superior de la matriz original
// N = tamaño de la matriz
/*(matr_sup debe de estar inicializada en 0 antes de llamar a este procedimiendo)*/
void matriz_sup(int **matrz, int **matrz_sup, int N)
{
	int i,j;

	for(i = 0;i < N ; i++;)
	{
		for(j = i+1;j < N ; j++)
		{
			matrz_sup[i][j] = matrz[i][j];

		}
	}
}

//matrz = matriz original, matrz_inf = matriz con solo la triangular inferior de la matriz original
// N = tamaño de la matriz
/*(matr_inf debe de estar inicializada en 0 antes de llamar a este procedimiendo)*/

void matriz_inf(int **matrz,int **matrz_inf,int N)
{
	int i,j;

	for(i = 0;i < N ; i++;)
	{
		for(j = i+1;j < N ; j++)
		{
			matrz_inf[j][i] = matrz[j][i];
		}
	}
}

//matrz = matriz original, matrz_diag = matriz con solo la diagonal de la matriz original
// N = tamaño de la matriz
/*(matr_diag debe de estar inicializada en 0 antes de llamar a este procedimiendo)*/

void matriz_diag(int **matrz,int **matrz_diag,int N)
{
	int i,j;

	for(i = 0;j < N ; i++)
	{
		matrz_inf[i][i] = matrz[i][i];
	}
}

/*matriz = matriz a inicializar, N = tamaño de la matriz*/

void inicializar_matr(int **matriz,int N)
{
	int i,j;

	for(i = 0;i < N;i++)
	{
		for(j = 0;j < N;j++)
		{
			matriz[i][j] = 0;
		}
	}

}