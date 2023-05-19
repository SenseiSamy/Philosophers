/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:05:14 by snaji             #+#    #+#             */
/*   Updated: 2023/05/19 23:53:53 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo, t_data *data)
{
	// if (data->number_of_philosophers % 2 == 0 && philo->id % 2 == 1)
	// 	usleep(10);
	if (data->forks[philo->left_fork].fork == -1)
	{
		fork_change_value(&data->forks[philo->left_fork], philo->id);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
	}
	else if (data->forks[philo->right_fork].fork == -1)
	{
		fork_change_value(&data->forks[philo->right_fork], philo->id);
		printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
	}
	else if (data->forks[philo->left_fork].fork == philo->id
		&& data->forks[philo->right_fork].fork == philo->id)
		philo->state = eating;
}

static void	eat(t_philo *philo, t_data *data, struct timeval *eat_time,
	int *nb_eat)
{
	printf("%ld %d is eating\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	*nb_eat += 1;
	if (gettimeofday(eat_time, NULL) == -1)
		pthread_exit(NULL);
	usleep(data->time_to_eat * 1000);
	fork_change_value(&data->forks[philo->left_fork], -1);
	fork_change_value(&data->forks[philo->right_fork], -1);
	philo->state = sleeping;
}

static void	sleeep(t_philo *philo, t_data *data)
{
	printf("%ld %d is sleeping\n", time_passed(data->init_time) / 1000,
		philo->id + 1);
	usleep(data->time_to_sleep * 1000);
	philo->state = thinking;
}

static int	check_time(t_data *data, t_philo *philo, struct timeval eat_time)
{
	if (time_passed(eat_time) > (size_t)(data->time_to_die * 1000))
	{
		printf("%ld %d is dead\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
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
