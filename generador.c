/** Generador de Casos Jhon Coello */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv)
{
    int dimension;
    if (argc > 1)
    {
        dimension = atoi(argv[1]);
    }
    else
    {
        dimension = 10;
    }

    srand(time(NULL));

    printf("%d\n", dimension);
    printf("0.00001\n");
    printf("%d\n", dimension);
    for (int i = 0; i < dimension; i++)
    {
        printf("%1.2f ", 0e0);
    }
    printf("\n");

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            if(i == j)
            {
                printf("%lf ", (sin(rand()) + dimension) * dimension);
            }
            else
            {
                printf("%lf ", (sin(rand()) + 1e0) * (dimension / 2e0));
            }
        }
        printf("\n");
    }
    for (int i = 0; i < dimension; i++)
    {
        printf("%lf ", (sin(rand()) + dimension) * dimension);
    }
    return 0;
}