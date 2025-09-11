/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:00:37 by haloztur          #+#    #+#             */
/*   Updated: 2025/09/11 11:40:25 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stopped(t_simulation *sim)
{
	int	ret;

	pthread_mutex_lock(&sim->death_mutex);
	ret = sim->someone_died;
	pthread_mutex_unlock(&sim->death_mutex);
	return (ret);
}

void	run_one_philo(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_status(p, "has taken a fork");
	ft_usleep(p->sim->time_to_die);
	pthread_mutex_unlock(p->left_fork);
}

void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		usleep(1000 * (p->id % 10));
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
	}
}

void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(&p->sim->meal_mutex);
	p->last_meal_time = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->sim->meal_mutex);
	print_status(p, "is eating");
	ft_usleep(p->sim->time_to_eat);
}
