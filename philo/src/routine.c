/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:05:14 by snaji             #+#    #+#             */
/*   Updated: 2023/05/12 02:29:14 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think2(t_philo *philo, t_data *data)
{
	if (data->forks[philo->right_fork].fork == -1)
	{
		fork_change_value(&data->forks[philo->right_fork], philo->id);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
	}
	if (data->forks[philo->left_fork].fork == -1)
	{
		fork_change_value(&data->forks[philo->left_fork], philo->id);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
	}
	if (data->forks[philo->left_fork].fork == philo->id
		&& data->forks[philo->right_fork].fork == philo->id)
		philo->state = eating;
}

void	think(t_philo *philo, t_data *data)
{
	if (data->forks[philo->left_fork].fork == -1)
	{
		fork_change_value(&data->forks[philo->left_fork], philo->id);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
	}
	if (data->forks[philo->right_fork].fork == -1)
	{
		fork_change_value(&data->forks[philo->right_fork], philo->id);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
	}
	if (data->forks[philo->left_fork].fork == philo->id
		&& data->forks[philo->right_fork].fork == philo->id)
		philo->state = eating;
}

void	eat(t_philo *philo, t_data *data, struct timeval *eat_time)
{
	printf("%ld %d is eating\n", time_passed(data->init_time) / 1000, philo->id + 1);
	if (gettimeofday(eat_time, NULL) == -1)
		pthread_exit(NULL);
	usleep(data->time_to_eat * 1000);
	fork_change_value(&data->forks[philo->left_fork], -1);
	fork_change_value(&data->forks[philo->right_fork], -1);
	philo->state = sleeping;
}

void	sleeep(t_philo *philo, t_data *data)
{
	printf("%ld %d is sleeping\n", time_passed(data->init_time) / 1000, philo->id + 1);
	usleep(data->time_to_sleep * 1000);
	philo->state = thinking;
}

void	*routine(void *ptr)
{
	t_philo			*philo;
	t_data			*data;
	struct timeval	eat_time;

	philo = (t_philo *)ptr;
	data = get_data();
	if (gettimeofday(&eat_time, NULL) == -1)
		pthread_exit(NULL);
	while (1)
	{
		if (time_passed(eat_time) > (size_t)(data->time_to_die * 1000))
			philo->state = dead;
		if (philo->state == thinking && philo->id % 2 == 0)
			think(philo, data);
		else if (philo->state == thinking)
			think2(philo, data);
		if (philo->state == eating)
			eat(philo, data, &eat_time);
		if (philo->state == sleeping)
			sleeep(philo, data);
	}
	pthread_exit(NULL);
}
