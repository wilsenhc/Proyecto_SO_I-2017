/*Generador de Casos Jhon Coello*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    int dimension;
    if (argc > 1) {
        dimension = atoi(argv[1]);
    } else {
        dimension = 10;
    }

    int i, j;
    srand(time(NULL));
    printf("%d\n0.00001\n%d\n", dimension, dimension);
    for (i = 0; i < dimension; i++)
        printf("%d ", 0);
    printf("\n");
    int m = ((dimension * dimension) - 10) + 1, n = (dimension * dimension) + dimension;
    for (i = 0; i < dimension; i++)
    {
        for (j = 0; j < dimension; j++)
            if(i == j)
                printf("%d ", rand() % (n - m) + m);
            else
                printf("%d ", rand() % dimension);
        printf("\n");
    }
    for (i = 0; i < dimension; i++)
        printf("%d ", rand() % dimension*2);
    return 0;
}