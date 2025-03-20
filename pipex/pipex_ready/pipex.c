/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:16:30 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/20 20:16:58 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_error(char *cmd, char **s_cmd, int code)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	ft_free(s_cmd);
	exit(code);
}

static void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd)
		exit_error(cmd, NULL, 1);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd || !s_cmd[0])
		exit_error(cmd, s_cmd, 127);
	path = paths(s_cmd[0], env);
	if (!path)
	{
		ft_free(s_cmd);
		ft_err(path);
	}
	if (execve(path, s_cmd, env) == -1)
		exit_error(s_cmd[0], s_cmd, 127);
}

static void	child_pro(int *fd, char **av, char **ep)
{
	int	fds;

	fds = open_file(av[1], 0);
	if (fds == -1)
	{
		if (access(av[1], R_OK) == -1 && access(av[1], F_OK) != -1)
		{
			ft_putstr_fd(av[1], 2);
			ft_putendl_fd(": Permission denied ", 2);
			exit (1);
		}
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit (1);
	}
	dup2(fds, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(fds);
	exec(av[2], ep);
}

static void	parent_pro(int *fd, char **av, char **ep)
{
	int	fds;

	fds = open_file(av[4], 1);
	if (fds == -1)
	{
		if (access(av[4], W_OK) == -1)
		{
			ft_putstr_fd(av[4], 2);
			ft_putendl_fd(": Permission denied ", 2);
			exit (1);
		}
		ft_putstr_fd(av[4], 2);
		ft_putendl_fd(" No such file or directory", 2);
		exit (1);
	}
	dup2(fds, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	close(fds);
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
