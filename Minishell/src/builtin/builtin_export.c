/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoysal <musoysal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:21:30 by musoysal          #+#    #+#             */
/*   Updated: 2025/06/27 16:55:58 by musoysal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_identifier_char(char c, int is_first)
{
	if (is_first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static char	*get_variable_name(char *arg)
{
	int		i;
	char	*name;

	if (!arg)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		name[i] = arg[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!is_valid_identifier_char(str[0], 1))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!is_valid_identifier_char(str[i], 0))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	builtin_export(char **args, t_req *req)
{
	char	*equal;
	char	*var_name;
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!args[1])
		return (builtin_env(req->envp));
	while (args[i])
	{
		var_name = get_variable_name(args[i]);
		if (!var_name || !is_valid_identifier(var_name))
		{
			print_export_error(args[i]);
			exit_code = 1;
		}
		else
		{
			equal = ft_strchr(args[i], '=');
			if (equal)
				mini_setenv_line(&req->envp, args[i]);
		}
		if (var_name)
			free(var_name);
		i++;
	}
	return (exit_code);
}
