/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:53:56 by atursun           #+#    #+#             */
/*   Updated: 2025/03/24 16:48:49 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/actions.h"

void	error_handling(void)
{
	ft_putendl_fd("Error", 2);
	exit(EXIT_FAILURE);
}

#include <stdio.h>
int	is_argv_null(char **str)
{
	int	i;
	int	j;

	if (!str[1][0])
		error_handling();
	i = 1;
	while (str[i])
	{
		j = 0;
		while (!str[i][j] || (str[i][j] == ' ') || (str[i][j] <=13 && str[i][j] >= 9))
			j++;
		if (!str[i][0] || !str[i][j + 1])
				error_handling();
		i++;
	}
	return (0);
}

int	is_int_range(char **str)
{
	long int	num;
	int			i;

	i = 0;
	while (str[i])
	{
		num = ft_atol(str[i]);
		if (num < INT_MIN || num > INT_MAX)
			return (free_args(str), -1);
		i++;
	}
	return (0);
}

int	is_digit(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if ((str[i][j] == '-' || str[i][j] == '+')
			&& (str[i][j + 1] == '\0' || str[i][j + 1] == ' '))
			return (free_args(str), -1);
		else if ((str[i][j] == '-' || str[i][j] == '+')
			&& (str[i][j + 1] != '\0' || str[i][j + 1] != ' '))
			j++;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (free_args(str), -1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_twin(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_atoi(str[i]) == ft_atoi(str[j]))
				return (free_args(str), -1);
			j++;
		}
		i++;
	}
	return (0);
}
