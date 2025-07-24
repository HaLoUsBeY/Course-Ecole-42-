/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:42:46 by haloztur          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:42 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static long	ft_latoi(const char *str)
{
	int		notr;
	long	result;

	notr = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			notr *= -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * notr);
}

int	ft_is_digit(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		if ((tab[i][j] == '-' || tab[i][j] == '+')
			&& (tab[i][j + 1] == '\0' || tab[i][j + 1] == ' '))
			return (ft_free(tab), -1);
		else if ((tab[i][j] == '+' || tab[i][j] == '-')
			&& ((tab[i][j + 1] != ' ') || tab[i][j + 1] != '\0'))
			j++;
		while (tab[i][j])
		{
			if (!ft_isdigit(tab[i][j]))
				return (ft_free(tab), -1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_is_duplicate(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_atoi(tab[i]) == ft_atoi(tab[j]))
			{
				ft_free(tab);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_is_int(char **av)
{
	int		i;
	long	num;

	i = 0;
	while (av[i])
	{
		if (ft_strlen(av[i]) > 12)
			return (ft_free(av), -1);
		num = ft_latoi(av[i]);
		if (num < -2147483648 || num > 2147483647)
			return (ft_free(av), -1);
		i++;
	}
	return (0);
}
