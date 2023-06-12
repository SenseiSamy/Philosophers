/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:40:59 by snaji             #+#    #+#             */
/*   Updated: 2023/06/12 19:51:55 by snaji            ###   ########.fr       */
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
	if (gettimeofday(&self->eat_time, NULL) == -1)
		exit(EXIT_FAILURE);
	++self->nb_eat;
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
		return (EXIT_FAILURE);
	pthread_create(&self->thread, NULL, &thread_check_death, self);
	pthread_detach(self->thread);
	if (id % 2 == 0 && data->think_time > 0)
		usleep(data->think_time * 1000);
	while (!(self->nb_eat >= data->number_of_times_each_philosopher_must_eat
		&& data->number_of_times_each_philosopher_must_eat >= 0))
	{
		if (self->state == thinking)
			think(self, data);
		else if (self->state == eating)
			eat(self, data);
		else if (self->state == sleeping)
			sleeep(self, data);
	}
	sem_post(data->simulation_ended);
	free_all(data);
	exit(EXIT_SUCCESS);
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
		else if (data->philos[i].pid == 0)
			philo_loop(data, i);
		++i;
	}
	pthread_create(&data->thread, NULL, &thread_main, data);
	pthread_join(data->thread, NULL);
	return (EXIT_SUCCESS);
}
