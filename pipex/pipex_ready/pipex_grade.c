/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_grade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:31:28 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/20 16:46:25 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *av, int a)
{
	int	result;

	if (a == 0)
		result = open(av, O_RDONLY, 0777);
	if (a == 1)
		result = open(av, O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0777);
	if (a == -1)
		exit(127);
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

static void	free_and_print(int found, char **get_path, char **s_cmd)
{
	ft_free(get_path);
	ft_free(s_cmd);
	if (found)
		ft_putendl_fd("pipex: Permission denied", 2);
	else
		ft_putendl_fd("pipex: No such file or directory", 2);
}

static char	*check_file(char *base, char *cmd, int *found)
{
	char	*part_path;
	char	*file;

	part_path = ft_strjoin(base, "/");
	file = ft_strjoin(part_path, cmd);
	free(part_path);
	if (!access(file, F_OK))
	{
		if (!access(file, X_OK))
			return (file);
		*found = 1;
	}
	free(file);
	return (NULL);
}

void	*paths(char *cmd, char **env)
{
	char	**get_path;
	char	**s_cmd;
	char	*file;
	int		i;
	int		found;

	get_path = ft_split(rmpaths("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	i = 0;
	found = 0;
	while (get_path[i])
	{
		file = check_file(get_path[i], s_cmd[0], &found);
		if (file)
		{
			ft_free(get_path);
			ft_free(s_cmd);
			return (file);
		}
		i++;
	}
	free_and_print(found, get_path, s_cmd);
	return (NULL);
}
