/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:05:58 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 13:06:39 by haloztur         ###   ########.fr       */
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
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long long)time.tv_sec * 1000ULL
		+ (unsigned long long)(time.tv_usec / 1000ULL));
}
