/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:20:00 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 16:35:58 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate_enough(t_simulation *sim)
{
	unsigned int	i;
	unsigned int	done;

	if (sim->must_eat_count == 0)
		return (0);
	done = 0;
	pthread_mutex_lock(&sim->meal_mutex);
	i = 0;
	while (i < sim->philosopher_count)
	{
		if (sim->philos[i].meals_eaten >= sim->must_eat_count)
			done++;
		i++;
	}
	pthread_mutex_unlock(&sim->meal_mutex);
	return (done == sim->philosopher_count);
}

static void	handle_death(t_simulation *sim, unsigned int i)
{
	sim->someone_died = 1;
	pthread_mutex_unlock(&sim->death_mutex);
	pthread_mutex_lock(&sim->print_mutex);
	printf("%llu %u %s\n",
		get_time_ms() - sim->start_time,
		sim->philos[i].id, "died");
	pthread_mutex_unlock(&sim->print_mutex);
}

static int	check_death(t_simulation *sim)
{
	unsigned int		i;
	unsigned long long	now;

	i = 0;
	now = get_time_ms();
	while (i < sim->philosopher_count)
	{
		pthread_mutex_lock(&sim->meal_mutex);
		if ((now - sim->philos[i].last_meal_time) >= sim->time_to_die)
		{
			pthread_mutex_unlock(&sim->meal_mutex);
			pthread_mutex_lock(&sim->death_mutex);
			if (!sim->someone_died)
				handle_death(sim, i);
			else
				pthread_mutex_unlock(&sim->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&sim->meal_mutex);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		if (check_death(sim))
			break ;
		if (all_ate_enough(sim))
		{
			pthread_mutex_lock(&sim->death_mutex);
			sim->someone_died = 1;
			pthread_mutex_unlock(&sim->death_mutex);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
