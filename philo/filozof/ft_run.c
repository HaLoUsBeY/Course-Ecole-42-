/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:26:54 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 13:26:54 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep_and_think(t_philo *p)
{
	print_status(p, "is sleeping");
	ft_usleep(p->sim->time_to_sleep);
}

static void	wait(unsigned int id)
{
	if (id % 2 == 0)
		usleep(500);
}

static int	philo_should_stop(t_philo *p)
{
	if (stopped(p->sim))
		return (1);
	if (p->sim->must_eat_count > 0 && p->meals_eaten >= p->sim->must_eat_count)
		return (1);
	return (0);
}

static void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->sim->philosopher_count == 1)
	{
		run_one_philo(p);
		return (NULL);
	}
	wait(p->id);
	while (!philo_should_stop(p))
	{
		print_status(p, "is thinking");
		take_forks(p);
		if (stopped(p->sim))
		{
			drop_forks(p);
			break ;
		}
		philo_eat(p);
		drop_forks(p);
		if (philo_should_stop(p))
			break ;
		philo_sleep_and_think(p);
	}
	return (NULL);
}

void	start_threads(t_simulation *sim)
{
	pthread_t		monitor;
	unsigned int	i;

	pthread_mutex_lock(&sim->meal_mutex);
	i = 0;
	while (i < sim->philosopher_count)
		sim->philos[i++].last_meal_time = sim->start_time;
	pthread_mutex_unlock(&sim->meal_mutex);
	if (pthread_create(&monitor, NULL, monitor_routine, (void *)sim) != 0)
		error_exit("pthread_create monitor failed");
	i = 0;
	while (i < sim->philosopher_count)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
				(void *)&sim->philos[i]) != 0)
			error_exit("pthread_create philo failed");
		i++;
	}
	pthread_join(monitor, NULL);
}
