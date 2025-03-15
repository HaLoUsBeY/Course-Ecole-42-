#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int form(int a, int b, char *c)
{
    if (*c == '-')
        return (a - b);
    else 
        return (a + b);
}

int main(int ac, char **av)
{
    int a;
    pid_t pid;
    if (ac == 4) 
    {
        int nbr1 = atoi(av[1]);
        int nbr2 = atoi(av[3]);
        printf ("1. sayi = %d, 2. sayi = %d, yapilacak işlem = %c \n", nbr1, nbr2, av[2][0]);
        pid = fork();

        if (pid == -1)
        {  
            printf("fork başarısız");
            return(1);
        }
        if (pid == 0)
        {
            printf("şuan çoçuk süreçdeyiz ve sonuç = %d ,atana pid%d ve pid no %d\n", form(nbr1, nbr2, av[2]), pid, getpid());
        }
        else
            printf("şuan yine ana sürece geçtik atanan pid ve şuanki pid = %d \n", getppid() ,getpid());

    }
    else 
        printf("\n");
    return (0);
}