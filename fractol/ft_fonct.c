/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fonct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 09:31:36 by haloztur          #+#    #+#             */
/*   Updated: 2025/04/12 09:31:36 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_double(char *s)
{
	int		i;
	int		comma;

	i = 0;
	comma = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (comma)
				return (0);
			comma = 1;
		}
		else if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

double	ft_datoi(char *s)
{
	long	n1;
	double	n2;
	double	pow;
	int		sign;

	n1 = 0;
	n2 = 0;
	sign = 1;
	pow = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		++s;
	while (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign *= -1;
	while (*s && *s != '.')
		n1 = (n1 * 10) + (*s++ - '0');
	if (*s == '.')
		++s;
	while (*s)
	{
		pow /= 10;
		n2 = n2 +(*s++ - '0') * pow;
	}
	return ((n1 + n2) * sign);
}

int idk (char *s)
{
	if (!*s)
		return (0);
	else
		return (ft_double(s));
}
