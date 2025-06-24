#include "../../minishell.h"

int builtin_cd(t_shell *cmd, t_req *req)
{
	char *target;
	char *oldpwd = getcwd(NULL, 0);

	if (!cmd->full_cmd[1])
		target = mini_getenv("HOME", req->envp, 4);
	else if (!ft_strncmp(cmd->full_cmd[1], "-", 2))
	{
		target = mini_getenv("OLDPWD", req->envp, 6);
		if (target)
			ft_putendl_fd(target, STDOUT_FILENO); 
	}
	else
		target = ft_strdup(cmd->full_cmd[1]);

	if (!target || chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		free(target);
		return (1);
	}

	req->envp = mini_setenv("OLDPWD", oldpwd, req->envp, 6);
	free(oldpwd);

	char *newpwd = getcwd(NULL, 0);
	req->envp = mini_setenv("PWD", newpwd, req->envp, 3);
	free(newpwd);
	free(target);
	return (0);
}
