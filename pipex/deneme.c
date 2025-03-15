#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void main (void)
{
    int pipefd[2];
    char buffer[256] = { 0 };

    printf("parent pid : %d\n", getpid());
    pipe(pipefd);
    write(pipefd[1], "msg", 3);
    if (fork() > 0)
        return ; 
    read(pipefd[0], buffer, 3);

    printf("got from pipe : %s\n",buffer);
    printf("pid: %d\n",getpid());
}