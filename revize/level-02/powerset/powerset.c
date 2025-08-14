#include <stdio.h>
#include <stdlib.h>

void show(int *pick, int m)
{
    for (int i = 0; i < m; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", pick[i]);
    }
    printf("\n");
}

void go(int goal, int *arr, int n, int *pick, int m, int idx, int sum)
{
    if (idx == n)
    {
        if (sum == goal)
            show(pick, m);
        return;
    }
    // Elemanı al
    pick[m] = arr[idx];
    go(goal, arr, n, pick, m + 1, idx + 1, sum + arr[idx]);
    // Elemanı alma
    go(goal, arr, n, pick, m, idx + 1, sum);
}

int main(int ac, char **av)
{
    if (ac < 2)
        return (0);

    int goal = atoi(av[1]);
    int n = ac - 2;
    int *arr = malloc(sizeof(int) * n);
    int *pick = malloc(sizeof(int) * n);
    if (!arr || !pick)
    {
        free(arr);
        free(pick);
        return (1);
    }
    for (int i = 0; i < n; i++)
        arr[i] = atoi(av[i + 2]);

    go(goal, arr, n, pick, 0, 0, 0);

    free(arr);
    free(pick);
    return (0);
}
