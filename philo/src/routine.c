/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:05:14 by snaji             #+#    #+#             */
/*   Updated: 2023/05/22 22:06:11 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo, t_data *data)
{
	if (mutex_fork_equal(&data->forks[philo->left_fork], -1))
	{
		mutex_fork_assign(&data->forks[philo->left_fork], philo->id);
		pthread_mutex_lock(&data->printf);
		printf("%ld %d has taken a fork %d\n", time_passed(data->init_time) / 1000,
			philo->id + 1, philo->left_fork + 1);
		pthread_mutex_unlock(&data->printf);
	}
	else if (mutex_fork_equal(&data->forks[philo->right_fork], -1))
	{
		mutex_fork_assign(&data->forks[philo->right_fork], philo->id);
		pthread_mutex_lock(&data->printf);
		printf("%ld %d has taken a fork %d\n", time_passed(data->init_time) / 1000,
			philo->id + 1, philo->right_fork + 1);
		pthread_mutex_unlock(&data->printf);
	}
	else if (mutex_fork_equal(&data->forks[philo->left_fork], philo->id)
		&& mutex_fork_equal(&data->forks[philo->right_fork], philo->id))
		philo->state = eating;
}

static void	eat(t_philo *philo, t_data *data, struct timeval *eat_time,
	int *nb_eat)
{
	pthread_mutex_lock(&data->printf);
	printf("%ld %d is eating\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&data->printf);
	*nb_eat += 1;
	if (gettimeofday(eat_time, NULL) == -1)
		pthread_exit(NULL);
	usleep(data->time_to_eat * 1000);
	mutex_fork_assign(&data->forks[philo->left_fork], -1);
	mutex_fork_assign(&data->forks[philo->right_fork], -1);
	philo->state = sleeping;
}

static void	sleeep(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->printf);
	printf("%ld %d is sleeping\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&data->printf);
	usleep(data->time_to_sleep * 1000);
	philo->state = thinking;
	pthread_mutex_lock(&data->printf);
	printf("%ld %d is thinking\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&data->printf);
}

static int	check_time(t_data *data, t_philo *philo, struct timeval eat_time)
{
	pthread_mutex_lock(&data->simulation_ended_mutex);
	if (data->simulation_ended == 1)
		return (pthread_mutex_unlock(&data->simulation_ended_mutex), 1);
	pthread_mutex_unlock(&data->simulation_ended_mutex);
	if (time_passed(eat_time) > (size_t)(data->time_to_die * 1000))
	{
		pthread_mutex_lock(&data->printf);
		printf("%ld %d is dead\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
		pthread_mutex_unlock(&data->printf);
		pthread_mutex_lock(&data->simulation_ended_mutex);
		data->simulation_ended = 1;
		pthread_mutex_unlock(&data->simulation_ended_mutex);
		philo->state = dead;
		return (1);
	}
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo			*philo;
	t_data			*data;
	struct timeval	eat_time;
	int				nb_eat;

	philo = (t_philo *)ptr;
	data = get_data();
	nb_eat = 0;
	if (gettimeofday(&eat_time, NULL) == -1)
		pthread_exit(NULL);
	while (1)
	{
		if (nb_eat >= data->number_of_times_each_philosopher_must_eat
			&& data->number_of_times_each_philosopher_must_eat >= 0)
			break ;
		if (check_time(data, philo, eat_time))
			break ;
		if (philo->state == thinking)
			think(philo, data);
		else if (philo->state == eating)
			eat(philo, data, &eat_time, &nb_eat);
		else if (philo->state == sleeping)
			sleeep(philo, data);
	}
	pthread_exit(NULL);
}
