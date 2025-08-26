/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haloztur <haloztur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:42:39 by haloztur          #+#    #+#             */
/*   Updated: 2025/08/24 18:42:39 by haloztur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TYPE_H)
# define TYPE_H


#include <unistd.h>
#include <stdio.h>
#include <pthread.h>



typedef struct s_philo {
    int             id;
    int             left_fork;
    int             right_fork;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_t       thread;
} t_philo;

typedef struct s_simulation {
    int             philosopher_count;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    int             someone_died;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philo        *philos;
} t_simulation;




#endif