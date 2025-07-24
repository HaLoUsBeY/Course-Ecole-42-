/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_grade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:31:28 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/16 22:30:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_err(char *str)
{
	if (!str)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(str, 2);
		exit(127);
	}
}

void	ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	open_file(char *av, int a)
{
	int	result;

	if (a == 0)
	{
		result = open(av, O_RDONLY, 0777);
	}
	if (a == 1)
	{
		result = open(av, O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0777);
	}
	if (a == -1)
	{
		exit(1);
	}
	return (result);
}

static char	*rmpaths(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, j) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

void	*paths(char *cmd, char **env)
{
	char	**get_path;
	char	*part_path;
	char	**s_cmd;
	char	*file;
	int		i;

	get_path = ft_split((rmpaths("PATH", env)), ':');
	s_cmd = ft_split(cmd, ' ');
	i = -1;
	while (get_path[++i])
	{
		part_path = ft_strjoin(get_path[i], "/");
		file = ft_strjoin(part_path, s_cmd[0]);
		free(part_path);
		if (access(file, F_OK | X_OK) == 0)
		{
			free(s_cmd);
			return (file);
		}
		free(file);
	}
	ft_free(get_path);
	ft_free(s_cmd);
	return (cmd);
}
