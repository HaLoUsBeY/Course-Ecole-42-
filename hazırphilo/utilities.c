/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:05:58 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 16:35:46 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(const char *str)
{
	int	lnght;

	lnght = 0;
	while (str[lnght] != '\0')
		lnght++;
	return (lnght);
}

void	ft_usleep(unsigned int ms)
{
	unsigned long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(500);
}

void	error_exit(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
