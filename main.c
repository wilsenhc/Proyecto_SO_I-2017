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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int dimensionMatriz;
    int maximoIteraciones;
    double tolerancia;
    double **matrizA;
    double *vectorB, *vectorX, *vectorXInicial;
} Jacobi;



void jcobi(Jacobi J);
double sumatoria(Jacobi J,int i);
int comprobar(Jacobi J);

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
	jcobi(jacobi);

    return 0;
}


void jcobi(Jacobi J)
{

	int i,j,k,band;
	k = 0;
	band = 0;

	for(k = 0; k < J.maximoIteraciones && !band;k++)
	{
		for(i = 0; i < J.dimensionMatriz;i++)
		{
			J.vectorX[i] = (sumatoria(J,i) + J.vectorB[j]) / J.matrizA[i][i];
		}

		band = comprobar(J);

		for(j = 0;j < J.dimensionMatriz ; j++)
		{
			J.vectorXInicial[j] = J.vectorX[j];
		}

	}
	if(band)
	{
		printf("Solucion encontrada");
	}
	else
	{
		printf("se excedio de el numero de iteraciones");
	}

}


double sumatoria(Jacobi J,int i)
{
	int j;
	double total;

	total = 0e0;

	for(j = 0; j < J.maximoIteraciones;j++)
	{
		if(j != i)
		{
			total = total + (J.matrizA[i][j] * J.vectorXInicial[j]);
		}
	}
	return(total * -1);
}

int comprobar(Jacobi J)
{
	int i,band,k;
	band = 0;
	k = 0;
	for(i = 0; i < J.dimensionMatriz;i++)
	{
		if(fabs(J.vectorX[i]-J.vectorXInicial[i]) < J.tolerancia)
		{
			k++;
		}
	}
	if(k == i-1)
	{
		band = 1;
	}
	return(band);
}