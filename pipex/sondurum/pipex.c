/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:16:30 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/16 22:35:03 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd)
		ft_err(cmd);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(127);
	}
	path = paths(s_cmd[0], env);
	if (!path)
		ft_err(path);
	execve(path, s_cmd, env);
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(s_cmd[0], 2);
	ft_free(s_cmd);
	exit(127);
}

static void	child_pro(int *fd, char **av, char **ep)
{
	int	fds;

	fds = open_file(av[1], 0);
	if (fds == -1)
		perror("Unable to open input_file");
	dup2(fds, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	exec(av[2], ep);
}

static void	parent_pro(int *fd, char **av, char **ep)
{
	int	fds;

	fds = open_file(av[4], 1);
	if (fds == -1)
		perror("Unable to open outFile");
	dup2(fds, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	exec(av[3], ep);
}

int	main(int ac, char **av, char **ep)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
	{
		ft_putendl_fd("used: ./pipex infile cmd1 cmd2 outfile", 39);
		return (1);
	}
	else
	{
		pipe(fd);
		if (pipe(fd) == -1)
			return (perror("pipe fail"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork fail"), 1);
		if (pid == 0)
			child_pro(fd, av, ep);
		waitpid(pid, NULL, 0);
		if (pid != 0)
			parent_pro(fd, av, ep);
	}
	return (0);
}
