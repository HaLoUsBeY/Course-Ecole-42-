#include "../../minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

extern int g_exit_status;

static void set_fd(int fd_from, int fd_to)
{
	if (fd_from != fd_to)
	{
		dup2(fd_from, fd_to);
		close(fd_from);
	}
}

static void close_extra_fds(int keep1, int keep2)
{
	int fd_limit = 1024;
	for (int fd = 3; fd < fd_limit; fd++)
	{
		if (fd != keep1 && fd != keep2)
			close(fd);
	}
}

static void setup_and_exec(t_shell *cmd, t_req *req, int in_fd, int out_fd)
{
	int devnull;

	close_extra_fds(in_fd, out_fd);
	reset_signals();
	if (!cmd->full_cmd || !cmd->full_cmd[0] || cmd->full_cmd[0][0] == '\0')
	{
		ft_putendl_fd("minishell: empty command", 2);
		exit(0);
	}
	if (apply_redirects(cmd))
		exit(1);
	set_fd(cmd->infile != STDIN_FILENO ? cmd->infile : in_fd, STDIN_FILENO);
	set_fd(cmd->outfile != STDOUT_FILENO ? cmd->outfile : out_fd, STDOUT_FILENO);

	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);

	if (is_builtin(cmd->full_cmd[0]))
	{
		devnull = open("/dev/null", O_RDONLY);
		if (devnull != -1)
		{
			dup2(devnull, STDIN_FILENO);
			close(devnull);
		}
		run_builtin(cmd, req);
		exit(g_exit_status);
	}
	if (!cmd->full_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->full_cmd && cmd->full_cmd[0]
						  ? cmd->full_cmd[0]
						  : "(null)",
					  2);
		exit(127);
	}
	execve(cmd->full_path, cmd->full_cmd, req->envp);
	if (errno == EISDIR)
		ms_error(ERR_IS_DIR, cmd->full_path, 126);
	else if (errno == EACCES)
	{
		if (access(cmd->full_path, X_OK) == 0)
			ms_error(ERR_IS_DIR, cmd->full_path, 126);
		else
			ms_error(ERR_NO_PERM, cmd->full_path, 126);
	}
	else if (errno == ENOENT)
		ms_error(ERR_NO_CMD, cmd->full_path, 127);
	else
	{
		perror("execve");
		g_exit_status = 1;
	}
	exit(g_exit_status);
}

static pid_t exec_external_cmd(t_shell *cmd, t_req *req, int in_fd, int out_fd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		setup_and_exec(cmd, req, in_fd, out_fd);
	return (pid);
}

static void restore_io(int *backup_in, int *backup_out)
{
	if (*backup_out != -1)
	{
		dup2(*backup_out, STDOUT_FILENO);
		close(*backup_out);
	}
	if (*backup_in != -1)
	{
		dup2(*backup_in, STDIN_FILENO);
		close(*backup_in);
	}
}

static void exec_single_builtin(t_shell *cmd, t_req *req, int input_fd)
{
	int backup_out;
	int backup_in;

	backup_out = -1;
	backup_in = -1;
	if (!cmd->full_cmd || !cmd->full_cmd[0])
	{
		g_exit_status = 0;
		return;
	}
	if (apply_redirects(cmd) != 0)
	{
		g_exit_status = 1;
		return;
	}
	if (cmd->infile == STDIN_FILENO && input_fd != STDIN_FILENO)
	{
		backup_in = dup(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	else if (cmd->infile != STDIN_FILENO)
	{
		backup_in = dup(STDIN_FILENO);
		dup2(cmd->infile, STDIN_FILENO);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		backup_out = dup(STDOUT_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);
	}
	run_builtin(cmd, req);
	restore_io(&backup_in, &backup_out);
}

static int	handle_exec(
		t_shell *cmd,
		t_req *req,
		int *input_fd,
		pid_t *pid,
		int has_next)
{
	int	pipe_fd[2];
	int	out_fd;
	int	real_in;

	out_fd = STDOUT_FILENO;
	if (has_next)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		out_fd = pipe_fd[1];
	}
	real_in = *input_fd;
	if (cmd->infile != STDIN_FILENO)
	{
		if (*input_fd != STDIN_FILENO)
			close(*input_fd);
		real_in = cmd->infile;
	}
	*pid = exec_external_cmd(cmd, req, real_in, out_fd);
	if (real_in != STDIN_FILENO)
		close(real_in);
	if (has_next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	return (0);
}

void execute_cmds(t_list *cmds, t_req *req)
{
	t_list *node;
	t_shell *cmd;
	int input_fd;
	int prev_input_fd;
	pid_t *pids;
	int count;
	int i;
	int status;

	count = ft_lstsize(cmds);
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
	{
		perror("malloc");
		g_exit_status = 1;
		return;
	}
	node = cmds;
	input_fd = STDIN_FILENO;
	prev_input_fd = STDIN_FILENO;
	i = 0;
	while (node)
	{
		cmd = (t_shell *)node->content;
		if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0] || cmd->full_cmd[0][0] == '\0')
		{
			ft_putendl_fd("minishell: invalid or empty command", 2);
			g_exit_status = 0;
			pids[i] = -1;
			i++;
			node = node->next;
			continue;
		}
		if (count == 1 && is_builtin(cmd->full_cmd[0]))
		{
			exec_single_builtin(cmd, req, input_fd);
			input_fd = STDIN_FILENO;
			pids[i] = -1;
		}
		else if (handle_exec(cmd, req, &input_fd, &pids[i], !!node->next))
		{
			free(pids);
			return;
		}
		if (prev_input_fd != STDIN_FILENO)
			close(prev_input_fd);
		prev_input_fd = input_fd;
		i++;
		node = node->next;
	}
	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
		{
			waitpid(pids[i], &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	free(pids);
}
