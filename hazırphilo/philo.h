/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:28:28 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/28 16:40:42 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_simulation	t_simulation;

typedef struct s_philo
{
	unsigned int		id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	unsigned int		meals_eaten;
	unsigned long long	last_meal_time;
	pthread_t			thread;
	t_simulation		*sim;
}	t_philo;

typedef struct s_simulation
{
	unsigned int		philosopher_count;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		must_eat_count;
	int					someone_died;
	unsigned long long	start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
	t_philo				*philos;
}	t_simulation;

unsigned int		ft_atoi_u(const char *str);
int					ft_isspace(int c);
int					ft_isdigit(int c);
void				error_exit(const char *msg);

int					stopped(t_simulation *sim);
void				run_one_philo(t_philo *p);
void				take_forks(t_philo *p);
void				drop_forks(t_philo *p);
void				philo_eat(t_philo *p);

unsigned long long	get_time_ms(void);
void				ft_usleep(unsigned int ms);
void				print_status(t_philo *p, const char *status);

int					ft_check(int ac, char **av);
unsigned int		check_and_ret(char *str);

void				philo_init(int ac, char **av, t_simulation *sim);

void				start_threads(t_simulation *sim);
void				join_threads_and_cleanup(t_simulation *sim);
void				*monitor_routine(void *arg);

#endif
