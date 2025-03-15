#include "pipex.h"

void child_pro(int *fd, char **av, char ep)
{
	int fds;

	fds = O_file(av[1], 0);
	close(fd[0]);
	dup2(fds, 0);
	dup2(fd[1], 1);

}

void parent_pro(int *fd, char **av, char ep)
{
	int fds;

	fds = O_file(av[4], 1);
	close(fd[1]);
	dup2(fds, 1);
	dup2(fd[0], 0);
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
