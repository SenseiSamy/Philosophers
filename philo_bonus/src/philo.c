/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:40:59 by snaji             #+#    #+#             */
/*   Updated: 2023/06/23 20:22:11 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	think(t_philo *self, t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->printf);
	printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
		self->id + 1);
	sem_post(data->printf);
	sem_wait(data->forks);
	sem_wait(data->printf);
	printf("%ld %d has taken a fork\n", time_passed(data->init_time) / 1000,
		self->id + 1);
	sem_post(data->printf);
	self->state = eating;
	printf("%ld %d is eating\n", time_passed(data->init_time) / 1000,
		self->id + 1);
}

static void	eat(t_philo *self, t_data *data)
{
	sem_wait(data->eat_time);
	if (gettimeofday(&self->eat_time, NULL) == -1)
		exit(EXIT_FAILURE);
	sem_post(data->eat_time);
	++self->nb_eat;
	if (self->nb_eat == data->number_of_times_each_philosopher_must_eat
		&& data->number_of_times_each_philosopher_must_eat >= 0)
		sem_post(data->nb_finish_eat);
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	self->state = sleeping;
}

static void	sleeep(t_philo *self, t_data *data)
{
	sem_wait(data->printf);
	printf("%ld %d is sleeping\n", time_passed(data->init_time) / 1000,
		self->id + 1);
	sem_post(data->printf);
	usleep(data->time_to_sleep * 1000);
	self->state = thinking;
	sem_wait(data->printf);
	printf("%ld %d is thinking\n", time_passed(data->init_time) / 1000,
		self->id + 1);
	sem_post(data->printf);
	if (data->think_time > 0)
		usleep(data->think_time * 1000);
}

static int	philo_loop(t_data *data, int id)
{
	t_philo	*self;

	self = &data->philos[id];
	self->id = id;
	self->state = thinking;
	self->data = data;
	self->nb_eat = 0;
	if (gettimeofday(&self->eat_time, NULL) == -1)
		exit(EXIT_FAILURE);
	if (pthread_create(&self->thread, NULL, &thread_check_death, self) != 0)
		exit(EXIT_FAILURE);
	if (data->number_of_philosophers > 1 && self->id % 2 == 0)
		usleep(ft_min(data->time_to_eat, data->time_to_die) * 1000);
	while (1)
	{
		if (self->state == thinking)
			think(self, data);
		else if (self->state == eating)
			eat(self, data);
		else if (self->state == sleeping)
			sleeep(self, data);
	}
}

int	start_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			return (EXIT_FAILURE);
		if (data->philos[i].pid == 0)
			philo_loop(data, i);
		++i;
	}
	if (pthread_create(&data->thread2, NULL, &thread_main, data) != 0)
		return (kill_all_processes(data), EXIT_FAILURE);
	sem_wait(data->simulation_ended);
	kill_all_processes(data);
	i = 0;
	while (i++ < data->number_of_philosophers)
		sem_post(data->nb_finish_eat);
	if (pthread_join(data->thread2, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
