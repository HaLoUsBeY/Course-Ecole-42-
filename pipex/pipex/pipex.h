#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft.h"

int open_file(char *av, int a);
void *paths(char *cmd, char **env);
char *rmpaths(char *cmd, char **env);
void child_pro(int *fd, char **av, char **ep);
void parent_pro(int *fd, char **av, char** ep);
void exec(char *cmd, char **env);
void ft_free(char **arr);

#endif