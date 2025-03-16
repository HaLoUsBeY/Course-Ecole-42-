
#include "pipex.h"

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

int open_file(char *av, int a)
{
	int result;

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
		exit(0);
	}
	return (result);
}

char *rmpaths(char *cmd, char **env)
{
	char *res;
	int i = 0;
	int j = 0;
	while (env[i])
	{
		while (env[i][j] && env[i][j] != '=')
			j++;
		res = ft_substr(env[i][j], 0, j); 
		if (ft_strcmp(res, cmd) == 0)
		{
			free(res);
			return (env[i] + 1 + j);
		}
		free(res);
		i++;
	}
	return (res);
}


void *paths(char *cmd, char **env)
{
	char **get_path;
	char *part_path;
	char **s_cmd;
	char *file;
	int			i;

	get_path = ft_split((rmpaths("PATH", env)) ,':');
	s_cmd = ft_split(cmd, ' ');
	i = 0;
	while (get_path[i++])
	{
		part_path = ft_strjoin(get_path[i], '/');
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