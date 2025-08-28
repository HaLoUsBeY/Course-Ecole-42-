/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:06:13 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 13:15:27 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_simulation *sim)
{
	unsigned int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philosopher_count);
	if (!sim->forks)
		error_exit("malloc forks failed");
	i = 0;
	while (i < sim->philosopher_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
}

static void	init_philos(t_simulation *sim)
{
	unsigned int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->philosopher_count);
	if (!sim->philos)
		error_exit("malloc philos failed");
	i = 0;
	while (i < sim->philosopher_count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal_time = get_time_ms();
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[
			(i + 1) % sim->philosopher_count];
		sim->philos[i].sim = sim;
		i++;
	}
}

void	philo_init(int ac, char **av, t_simulation *sim)
{
	memset(sim, 0, sizeof(*sim));
	sim->philosopher_count = check_and_ret(av[1]);
	sim->time_to_die = check_and_ret(av[2]);
	sim->time_to_eat = check_and_ret(av[3]);
	sim->time_to_sleep = check_and_ret(av[4]);
	if (ac == 6)
		sim->must_eat_count = check_and_ret(av[5]);
	else
		sim->must_eat_count = 0;
	sim->someone_died = 0;
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->death_mutex, NULL);
	pthread_mutex_init(&sim->meal_mutex, NULL);
	sim->start_time = get_time_ms();
	init_forks(sim);
	init_philos(sim);
}
