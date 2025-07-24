#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <windows.h>
#include <process.h>

void child_pro(int *fd, char **av, char ep)
{
    int fd;

    fd = open();
}

void parent_pro(int *fd, char **av, char ep)
{

}

int main(int ac, char **av, char **ep)
{
    if (ac != 5) 
    {
        printf("Kullanım: ./pipex infile cmd1 cmd2 outfile\n");
        return (1);
    }
    else
    {
        int fd[2];
        pid_t pid;
        pipe(fd);

        if (pipe(fd) == -1)
        {
            perror("pipe basarisiz");
            return (1);
        }

        pid = fork();
        if (pid == -1)
        {
            peror("fork basarisiz");
            return (1);
        }
        if (pid == 0)
        {
            child_pro(fd, av, ep);
        }
        wait(NULL);
        parent_pro(fd, av, ep);
    }
    return (0);
}
