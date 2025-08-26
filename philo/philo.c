
#include "philo.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_PHILO 200

long long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
}

void ft_usleep(long long ms)
{
    long long start = get_time_ms();
    while (get_time_ms() - start < ms)
        usleep(500);
}

void print_status(t_simulation *sim, t_philo *philo, const char *msg)
{
    pthread_mutex_lock(&sim->print_mutex);
    if (!sim->someone_died)
        printf("%lld %d %s\n", get_time_ms() - sim->start_time, philo->id, msg);
    pthread_mutex_unlock(&sim->print_mutex);
}

typedef struct s_routine_arg {
    t_simulation *sim;
    t_philo *philo;
} t_routine_arg;

void *philo_routine(void *arg)
{
    t_routine_arg *args = (t_routine_arg *)arg;
    t_simulation *sim = args->sim;
    t_philo *philo = args->philo;
    if (philo->id % 2 == 0)
        ft_usleep(1); // deadlock önleme için küçük gecikme
    while (!sim->someone_died)
    {
        print_status(sim, philo, "is thinking");
        pthread_mutex_lock(&sim->forks[philo->right_fork]);
        print_status(sim, philo, "has taken a fork");
        pthread_mutex_lock(&sim->forks[philo->left_fork]);
        print_status(sim, philo, "has taken a fork");
        print_status(sim, philo, "is eating");
        philo->last_meal_time = get_time_ms();
        philo->meals_eaten++;
        ft_usleep(sim->time_to_eat);
        pthread_mutex_unlock(&sim->forks[philo->left_fork]);
        pthread_mutex_unlock(&sim->forks[philo->right_fork]);
        if (sim->must_eat_count > 0 && philo->meals_eaten >= sim->must_eat_count)
            break;
        print_status(sim, philo, "is sleeping");
        ft_usleep(sim->time_to_sleep);
    }
    free(args);
    return NULL;
}

void *monitor(void *arg)
{
    t_simulation *sim = (t_simulation *)arg;
    int i, done;
    while (!sim->someone_died)
    {
        done = 1;
        for (i = 0; i < sim->philosopher_count; i++)
        {
            if ((get_time_ms() - sim->philos[i].last_meal_time) > sim->time_to_die)
            {
                pthread_mutex_lock(&sim->print_mutex);
                if (!sim->someone_died)
                    printf("%lld %d died\n", get_time_ms() - sim->start_time, sim->philos[i].id);
                sim->someone_died = 1;
                pthread_mutex_unlock(&sim->print_mutex);
                return NULL;
            }
            if (sim->must_eat_count < 0 || sim->philos[i].meals_eaten < sim->must_eat_count)
                done = 0;
        }
        if (sim->must_eat_count > 0 && done)
        {
            pthread_mutex_lock(&sim->print_mutex);
            sim->someone_died = 1;
            pthread_mutex_unlock(&sim->print_mutex);
            return NULL;
        }
        usleep(1000);
    }
    return NULL;
}

int main(int ac, char **av)
{
    t_simulation sim;
    t_philo philos[MAX_PHILO];
    pthread_mutex_t forks[MAX_PHILO];
    pthread_t monitor_thread;
    int i;

    if (ac != 5 && ac != 6)
    {
        printf("Usage: %s philosopher_count time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
        return 1;
    }

    memset(&sim, 0, sizeof(sim));
    sim.philosopher_count = atoi(av[1]);
    sim.time_to_die = atoi(av[2]);
    sim.time_to_eat = atoi(av[3]);
    sim.time_to_sleep = atoi(av[4]);
    sim.must_eat_count = (ac == 6) ? atoi(av[5]) : -1;
    sim.someone_died = 0;
    sim.start_time = get_time_ms();
    sim.forks = forks;
    sim.philos = philos;
    pthread_mutex_init(&sim.print_mutex, NULL);

    if (sim.philosopher_count < 1 || sim.philosopher_count > MAX_PHILO)
    {
        printf("Error: philosopher_count must be between 1 and %d\n", MAX_PHILO);
        return 1;
    }

    for (i = 0; i < sim.philosopher_count; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (i = 0; i < sim.philosopher_count; i++)
    {
        philos[i].id = i + 1;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % sim.philosopher_count;
        philos[i].meals_eaten = 0;
        philos[i].last_meal_time = sim.start_time;
    }

    for (i = 0; i < sim.philosopher_count; i++) {
        t_routine_arg *args = malloc(sizeof(t_routine_arg));
        args->sim = &sim;
        args->philo = &philos[i];
        pthread_create(&philos[i].thread, NULL, philo_routine, args);
    }
    pthread_create(&monitor_thread, NULL, monitor, &sim);

    for (i = 0; i < sim.philosopher_count; i++)
        pthread_join(philos[i].thread, NULL);
    pthread_join(monitor_thread, NULL);

    for (i = 0; i < sim.philosopher_count; i++)
        pthread_mutex_destroy(&forks[i]);
    pthread_mutex_destroy(&sim.print_mutex);
    return 0;
}