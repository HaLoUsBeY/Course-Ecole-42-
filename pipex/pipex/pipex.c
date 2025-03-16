#include "pipex.h"

void exec(char *cmd, char **env)
{
    char **s_cmd;
    char *path;

    s_cmd = ft_split(cmd, ' ');   
    path = paths(s_cmd[0], env);
    printf("Çalıştırılacak komut: %s\n", path);  
    if (execve(path, s_cmd, env) == -1)  
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(s_cmd[0], 2);
        ft_free(s_cmd);
        exit(0);
    }
}


void child_pro(int *fd, char **av, char **ep)
{
	int fds;

	fds = open_file(av[1], 0);
	dup2(fds, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	exec(av[2], ep);
}

void parent_pro(int *fd, char **av, char** ep)
{
	int fds;

	fds = open_file(av[4], 1);
	dup2(fds, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	exec(av[3], ep);
}

int main(int ac, char **av, char **ep)
{
	if (ac != 5) 
	{
		ft_putendl_fd("used: ./pipex infile cmd1 cmd2 outfile",39);
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
			perror("fork basarisiz");
			return (1);
		}
		if (pid == 0)
		{
			child_pro(fd, av, ep);
		}
		waitpid(pid, NULL, 0);
		parent_pro(fd, av, ep);
	}
	return (0);
}
