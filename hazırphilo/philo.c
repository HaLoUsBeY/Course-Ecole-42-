/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:28:36 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 19:23:43 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads_and_cleanup(t_simulation *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->philosopher_count)
		pthread_join(sim->philos[i++].thread, NULL);
	i = 0;
	while (i < sim->philosopher_count)
		pthread_mutex_destroy(&sim->forks[i++]);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	pthread_mutex_destroy(&sim->meal_mutex);
	free(sim->philos);
	free(sim->forks);
	memset(sim, 0, sizeof(t_simulation));
	memset(sim->philos, 0, sizeof(t_philo) * sim->philosopher_count);
}

int	main(int ac, char **av)
{
	t_simulation	sim;

	if ((ac != 5 && ac != 6) || ft_check(ac, av))
		error_exit("incorrect usage");
	philo_init(ac, av, &sim);
	start_threads(&sim);
	join_threads_and_cleanup(&sim);
	return (0);
}
