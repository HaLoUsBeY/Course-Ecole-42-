#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main (void)
{
    int fd[2];
    char buffer[20];
    char tampon[20];
    if(pipe(fd) == -1)
    {
        perror("pipe başarısız");
        return (1);
    }

    int fds = open("abc.txt",O_RDONLY);
    read(fds,buffer,20);
    write(fd[1], &tampon, sizeof(tampon));
    read(fd[0],&buffer,14);
    
    printf("%s",buffer);



    return (0);
}