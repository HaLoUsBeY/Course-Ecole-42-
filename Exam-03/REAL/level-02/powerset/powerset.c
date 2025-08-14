#include <stdio.h>
#include <stdlib.h>

void show(int *fix, int fixsize)
{
    for (int i = 0; i < fixsize; i++)
    {
        if (i > 0 )
            printf(" ");
        printf("%d", fix[i]);
    }
    printf("\n");
}

void go(int goal, int *arg, int argsize, int *fix, int fixsize, int idx, int sum)
{
    if (idx == argsize)
    {
        if (sum == goal)
            show(fix, fixsize);
        return;
    }
    fix[fixsize] = arg[idx];
    go(goal, arg, argsize, fix, fixsize + 1, idx + 1, sum + arg[idx]);
    go(goal, arg, argsize, fix, fixsize, idx + 1, sum);
}

int main (int ac, char **av)
{
    if (ac < 2)
        return 1;
    int goal = atoi(av[1]);
    int argsize = ac - 2;
    int *arg = malloc(sizeof(int) * argsize);
    int *fix = malloc(sizeof(int) * argsize);

    if (!arg || !fix)
    {
        free(arg);
        free(fix);
        return 1;
    }

    for (int i = 0; i < argsize; i++)
        arg[i] = atoi(av[i + 2]);
    
    go (goal, arg, argsize, fix, 0, 0, 0);
    free(arg);
    free(fix);
    return (0);
}