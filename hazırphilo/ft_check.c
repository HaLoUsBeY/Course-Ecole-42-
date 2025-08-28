/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:37:59 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 19:48:08 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_arg(char *arg)
{
	int	j = 0;
	unsigned long long num = 0;

	if (!arg || ft_isspace(arg[0]))
		return (1);
	while (arg[j])
	{
		if (!ft_isdigit(arg[j]))
			return (1);
		j++;
	}
	j = 0;
	while (arg[j])
	{
		num = num * 10 + (arg[j] - '0');
		if (num > 4294967295ULL)
			return (1);
		j++;
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
