
#include "pipex.h"

void ft_free(char **arr)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (arr[j])
	{
		while (arr[j][i])
		{
			free(arr[j][i]);
			i++;
		}
		free(are[j]);
                j++;
	}
}

int open_file(char *av, int a)
{
	int result;

	if (!a)
	{
		result = open(av, O_RDONLY, 0777);
		return (result);
	}
	if (a == 1)
	{
		result = open(av, O_CREAT | O_APPEND | O_WRONLY | O_TRUNC, 0777);
		return (result);
	}
	if (a == -1)
	{
		//exit(0);
		return (0);
	}
}

char *rmpaths(char *cmd, char **env)
{
	char *res;
	int i = 0;
	int j = 0;
	while (env[i][j] && env[i][j] != '=')
		j++;
	res = ft_substr(env[i][j], j, NULL); 
	if (ft_strncmp(res, env[i][j], j) == 0)
		{
			free(res);
			return (env[i][j] + 1 + j);
		}
		free(res);
	i++;
	return (res);
}


void *paths(char *cmd, char **env)
{
	char **get_path;
	char *part_path;
	char **s_cmd;
	char *file;
	int i;

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

}