#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int *pol;
int N;

int abs2(int n){return n < 0 ? -n : n;}


int safe(int y, int x)
{
    for(int i = 0; i < x; i++)
        if (pol[i] == y || (abs2(pol[i] - y) == abs2(i - x)))
            return 0;
    return 1;
}

void prints(void)
{
    for(int i = 0; i < N; i++)
        printf("%d%c",pol[i], (i == N -1 ? '\n' : ' '));
}

void solve(int x)
{
    if (x == N){prints(); return;}
    for (int y = 0; y < N ; y++)
        if (safe(y, x))
        {
            pol[x] = y;
            solve(x + 1);
        }
}
int main (int ac, char **av)
{
    if (ac != 2)
    {
        write(1,"\n",1);
        return 1;
    }
    N = atoi(av[1]);
    if (N < 4)
    {
        write(1,"\n",1);
        return 1;
    }
    pol = malloc(sizeof(int) * N);
    solve(0);
    free(pol);
    return 0;
}
