/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:40:59 by snaji             #+#    #+#             */
/*   Updated: 2023/05/29 19:33:56 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	think(t_philo *self, t_data *data)
{

}

static void	eat(t_philo *self, t_data *data)
{
	
}

static void	sleeep(t_philo *self, t_data *data)
{
	
}

int	philo_loop(t_data *data, int id)
{
	t_philo	*self;

	self = &data->philos[id];
	if (gettimeofday(&self->eat_time, NULL) == -1)
		return (EXIT_FAILURE);
	self->nb_eat = 0;
	while (self->state != dead)
	{

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
		else if (data->philos[i].pid == 0)
			philo_loop(data, i);
		++i;
	}
}
