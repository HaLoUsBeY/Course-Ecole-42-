/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:28:36 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/27 20:20:00 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Ölüm veya bitiş flag'i */
static int	stopped(t_simulation *sim)
{
	int ret;

	pthread_mutex_lock(&sim->death_mutex);
	ret = sim->someone_died;
	pthread_mutex_unlock(&sim->death_mutex);
	return (ret);
}

/* Tek filozof özel durumu */
static void	run_one_philo(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_status(p, "has taken a fork");
	/* başka çatal yok -> ölmeden önce bekle */
	ft_usleep(p->sim->time_to_die);
	pthread_mutex_unlock(p->left_fork);
}

/* Çatal alma (deadlock önlemek için sıralı) */
static void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
	}
}

static void	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void	philo_eat(t_philo *p)
{
	/* Yemek başlıyor */
	pthread_mutex_lock(&p->sim->meal_mutex);
	p->eating = 1;
	p->last_meal_time = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->sim->meal_mutex);

	print_status(p, "is eating");
	ft_usleep(p->sim->time_to_eat);

	pthread_mutex_lock(&p->sim->meal_mutex);
	p->eating = 0;
	pthread_mutex_unlock(&p->sim->meal_mutex);
}

static void	*philo_routine(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;

	if (p->sim->philosopher_count == 1)
	{
		run_one_philo(p);
		return (NULL);
	}

	if (p->id % 2 == 0)
		usleep(1000); /* küçük offset */

	while (!stopped(p->sim))
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

		if (p->sim->must_eat_count > 0
			&& p->meals_eaten >= p->sim->must_eat_count)
			break ;

		print_status(p, "is sleeping");
		ft_usleep(p->sim->time_to_sleep);
	}
	return (NULL);
}

void	start_threads(t_simulation *sim)
{
	pthread_t	monitor;
	unsigned int i;

	/* last_meal_time başlangıç ayarı */
	pthread_mutex_lock(&sim->meal_mutex);
	for (i = 0; i < sim->philosopher_count; i++)
		sim->philos[i].last_meal_time = sim->start_time;
	pthread_mutex_unlock(&sim->meal_mutex);

	/* Monitor */
	if (pthread_create(&monitor, NULL, monitor_routine, sim) != 0)
		error_exit("pthread_create monitor failed");

	/* Filozoflar */
	i = 0;
	while (i < sim->philosopher_count)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
				&sim->philos[i]) != 0)
			error_exit("pthread_create philo failed");
		i++;
	}

	/* Monitor bekle – ardından tüm filozoflar beklenir */
	pthread_join(monitor, NULL);
}

void	join_threads_and_cleanup(t_simulation *sim)
{
	unsigned int i;
	for (i = 0; i < sim->philosopher_count; i++)
		pthread_join(sim->philos[i].thread, NULL);
	for (i = 0; i < sim->philosopher_count; i++)
		pthread_mutex_destroy(&sim->forks[i]);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	pthread_mutex_destroy(&sim->meal_mutex);
	free(sim->philos);
	free(sim->forks);
}

int	main(int ac, char **av)
{
	t_simulation sim;

	if ((ac != 5 && ac != 6) || ft_check(ac, av))
		error_exit("incorrect usage");
		
	philo_init(ac, av, &sim);
	start_threads(&sim);
	join_threads_and_cleanup(&sim);
	return (0);
}
