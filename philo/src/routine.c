/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:05:14 by snaji             #+#    #+#             */
/*   Updated: 2023/06/13 17:41:33 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo, t_data *data)
{
	if (sim_end(philo, data) == true)
		return ;
	if (mutex_fork_equal(&data->forks[philo->left_fork], -1) == true
		&& mutex_fork_equal(&data->forks[philo->right_fork], -1) == true
		&& philo->right_fork != philo->left_fork)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork].mutex);
		pthread_mutex_lock(&data->forks[philo->right_fork].mutex);
		data->forks[philo->left_fork].fork = philo->id;
		data->forks[philo->right_fork].fork = philo->id;
		pthread_mutex_unlock(&data->forks[philo->left_fork].mutex);
		pthread_mutex_unlock(&data->forks[philo->right_fork].mutex);
		pthread_mutex_lock(&data->printf);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
		pthread_mutex_unlock(&data->printf);
		philo->state = eating;
	}
}

static void	eat(t_philo *philo, t_data *data)
{
	if (sim_end(philo, data) == true)
		return ;
	pthread_mutex_lock(&data->printf);
	printf("%ld %d is eating\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&data->printf);
	philo->nb_eat += 1;
	if (gettimeofday(&philo->eat_time, NULL) == -1)
		pthread_exit(NULL);
	if (data->time_to_eat > data->time_to_die)
		usleep(data->time_to_die * 1000);
	else
		usleep(data->time_to_eat * 1000);
	mutex_fork_assign(&data->forks[philo->left_fork], -1);
	mutex_fork_assign(&data->forks[philo->right_fork], -1);
	philo->state = sleeping;
}

static void	sleeep(t_philo *philo, t_data *data)
{
	if (sim_end(philo, data) == true)
		return ;
	pthread_mutex_lock(&data->printf);
	printf("%ld %d is sleeping\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&data->printf);
	if (time_passed(philo->eat_time) + (size_t)(data->time_to_sleep * 1000)
		> (size_t)(data->time_to_die * 1000))
		usleep(data->time_to_die * 1000 - time_passed(philo->eat_time));
	else
		usleep(data->time_to_sleep * 1000);
	if (sim_end(philo, data) == true)
		return ;
	philo->state = thinking;
	pthread_mutex_lock(&data->printf);
	printf("%ld %d is thinking\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	pthread_mutex_unlock(&data->printf);
	if (data->think_time > 0)
		usleep(data->think_time * 1000);
}

void	*philo_routine(void *ptr)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)ptr;
	data = philo->data;
	philo->nb_eat = 0;
	if (gettimeofday(&philo->eat_time, NULL) == -1)
		pthread_exit(NULL);
	while (philo->state != dead)
	{
		if (philo->nb_eat >= data->number_of_times_each_philosopher_must_eat
			&& data->number_of_times_each_philosopher_must_eat >= 0)
			break ;
		if (philo->state == thinking)
			think(philo, data);
		else if (philo->state == eating)
			eat(philo, data);
		else if (philo->state == sleeping)
			sleeep(philo, data);
	}
	pthread_exit(NULL);
}
