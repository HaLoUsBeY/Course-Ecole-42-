#include <stdio.h>
#include <stdlib.h>

void show(int *pick, int m)
{
    for (int i = 0; i < m ; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d",pick[i]);
    }
    printf("\n");
}


void go(int h, int *al, int o, int *us, int b, int e, int y)
{

}