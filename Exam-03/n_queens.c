#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int N;
int *pos;
int abs2(int n){return (n < 0) ? -n :n;}

int safe(int y, int x)
{
    for (int i = 0; i < x ; i++)
        if (pos[i] == y || (abs2(pos[i] - y) == abs2(i - x)))
            return 0;
    return 1;
}


void prints(void)
{
    for (int i = 0; i < N ; i++)
        printf("%d%c",pos[i], (i == N - 1) ? '\n' : ' ');
}



void solve(int x)
{
    if (x == N)
    {
        prints();
        return;
    }

    for (int y = 0; y < N; y++)
    {
        if (safe(y, x))
        {
            pos[x] = y;
            solve(x + 1);
        }
    }
}



int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    N = atoi(av[1]);
    pos = malloc(sizeof(int) * N);
    solve(0);
    free(pos);
    return 0;
}