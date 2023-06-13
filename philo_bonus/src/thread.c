/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:30:21 by snaji             #+#    #+#             */
/*   Updated: 2023/06/13 16:46:38 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*thread_check_death(void *ptr)
{
	t_philo	*self;

	self = (t_philo *)ptr;
	pthread_detach(self->thread);
	while (1)
	{
		if (time_passed(self->eat_time) > (size_t)(self->data->time_to_die
			* 1000))
		{
			sem_wait(self->data->printf);
			printf("%ld %d died\n", time_passed(self->data->init_time) / 1000,
				self->id + 1);
			sem_post(self->data->simulation_ended);
			pthread_exit(EXIT_SUCCESS);
		}
		usleep(500);
	}
}

void	*thread_main(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	sem_wait(data->simulation_ended);
	i = 0;
	while (i < data->number_of_philosophers)
		kill(data->philos[i++].pid, SIGKILL);
	pthread_exit(EXIT_SUCCESS);
}
