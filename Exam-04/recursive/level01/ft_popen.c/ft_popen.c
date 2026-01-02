#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    if (!file || !argv || (type != 'r' && type != 'w'))
        return -1;
    
    int fd[2];
    if (pipe(fd) == -1)
        return -1;
    
    pid_t pid = fork();
    if (pid == -1)
    {
        close(fd[0]);
        close(fd[1]);
        return -1;
    }

    if (type == 'r')
    {
        if (pid == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(file, argv);
            exit(1);
        }
        close(fd[1]);
        return (fd[0]);
    }
    else
    {
        if (pid == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execvp(file, argv);
            exit(1);
        }
        close(fd[0]);
        return(fd[1]);
    }
}

#include <stdio.h>

int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	dup2(fd, 0);
	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
	FILE *file = fdopen(fd, "r");
	char line[1024];
	while (fgets(line, sizeof(line), file))
		printf("%s", line);
	fclose(file);
}