/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:30:21 by snaji             #+#    #+#             */
/*   Updated: 2023/06/23 19:01:22 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_check_death(void *ptr)
{
	t_philo	*self;

	self = (t_philo *)ptr;
	while (1)
	{
		sem_wait(self->data->eat_time);
		if (time_passed(self->eat_time) > (size_t)(self->data->time_to_die
			* 1000))
		{
			sem_wait(self->data->printf);
			printf("%ld %d died\n", time_passed(self->data->init_time) / 1000,
				self->id + 1);
			sem_post(self->data->simulation_ended);
			return (NULL);
		}
		sem_post(self->data->eat_time);
		usleep(500);
	}
}

void	*thread_main(void *ptr)
{
	t_data	*data;
	int		n;

	data = (t_data *)ptr;
	n = 0;
	while (1)
	{
		sem_wait(data->nb_finish_eat);
		++n;
		if (n == data->number_of_philosophers)
			break ;
	}
	sem_post(data->simulation_ended);
	return (NULL);
}
