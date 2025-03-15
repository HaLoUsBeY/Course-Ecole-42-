#include <unistd.h>
#include <stdio.h>


int main (void)
{
    int a = 10;
    int b = 15;
    int fd[2];
    char buffer[20];
    // if (pipe(fd) == -1) {
    //     perror("pipe oluşturulamadı");
    //     return 1;
    // }
    pipe(fd);
    printf("ana süreçten iletişim alımı başladı\n");

    pid_t pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        printf("çoçuk süreçten iletişim verme başladı\n");
        write(fd[1],"10 + 15 == 25", 14);
        close(fd[1]);
    }
    else 
    {
        close(fd[1]);
        read(fd[0],&buffer,14);
        printf("%s",buffer);
        close(fd[0]);
    }

    return (0);
}