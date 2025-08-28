/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:29:16 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 16:35:42 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_status(t_philo *p, const char *status)
{
	unsigned long long	now;
	unsigned long long	rel;

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
	pthread_mutex_lock(&p->sim->death_mutex);
	if (!p->sim->someone_died)
		printf("%llu %u %s\n", rel, p->id, status);
	pthread_mutex_unlock(&p->sim->death_mutex);
	pthread_mutex_unlock(&p->sim->print_mutex);
}
