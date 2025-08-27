/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:28:22 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/27 20:20:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *p, const char *status)
{
	unsigned long long	now;
	unsigned long long	rel;

	/* Ölümden sonra yazma yok */
	pthread_mutex_lock(&p->sim->death_mutex);
	if (p->sim->someone_died)
	{
		pthread_mutex_unlock(&p->sim->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&p->sim->death_mutex);

	now = get_time_ms();
	rel = now - p->sim->start_time;

	pthread_mutex_lock(&p->sim->print_mutex);
	/* Yazarken de ölüm tekrar kontrol (yarış önleme) */
	pthread_mutex_lock(&p->sim->death_mutex);
	if (!p->sim->someone_died)
		printf("%llu %u %s\n", rel, p->id, status);
	pthread_mutex_unlock(&p->sim->death_mutex);
	fflush(stdout);
	pthread_mutex_unlock(&p->sim->print_mutex);
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
	write(2, msg, strlen(msg));
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

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

unsigned int	ft_atoi_u(const char *str)
{
	unsigned int	res;
	int				i;

	i = 0;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

unsigned long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long long)tv.tv_sec * 1000ULL
		+ (unsigned long long)(tv.tv_usec / 1000ULL));
}
