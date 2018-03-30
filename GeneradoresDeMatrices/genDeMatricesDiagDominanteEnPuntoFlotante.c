/*Generador de Casos Jhon Coello*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
	float i, j;
	float dimension;
	float aux;
	srand(time(NULL));
	scanf("%f", &dimension);
	printf("%d\n0.00001\n%d\n", (int)dimension, (int)(dimension*dimension));
	for (i = 0; i < dimension; i++)
        printf("%1.2f ", 0.0);
	printf("\n");
	//float m = ((dimension * dimension) - 10) + 1, n = (dimension * dimension) + dimension;
    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
			if(i == j)
				printf("%f ", (sin((float)rand())+dimension)*dimension);
				//valor=(sin((float)rand())+1.0)*50.0;
			else
            	printf("%f ", (sin((float)rand())+1.0)*dimension/2);
        printf("\n");
    }
	for (i = 0; i < dimension; i++)
		printf("%f ", (sin((float)rand())+dimension)*dimension);
	return 0;
}