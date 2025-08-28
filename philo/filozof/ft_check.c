/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:37:59 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 13:13:04 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_space(char c, char next, int *flag)
{
	if (ft_isspace(c) && next)
	{
		if (++(*flag) == 1)
			return (1);
		return (0);
	}
	return (-1);
}

static int	ft_check_arg(char *arg)
{
	int	j;
	int	flag;
	int	res;

	j = 0;
	flag = 0;
	if (ft_isspace(arg[0]))
		return (1);
	while (arg[j])
	{
		if (ft_isdigit(arg[j]))
			j++;
		else
		{
			res = is_valid_space(arg[j], arg[j + 1], &flag);
			if (res == 1)
				j++;
			else
				return (1);
		}
	}
	return (0);
}

int	ft_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_check_arg(av[i]))
			return (1);
		i++;
	}
	return (0);
}

unsigned int	check_and_ret(char *str)
{
	unsigned int	num;

	if (ft_check(2, (char *[]){NULL, str}))
		error_exit("incorrect usage");
	num = ft_atoi_u(str);
	if (num == 0)
		error_exit("incorrect usage");
	return (num);
}
