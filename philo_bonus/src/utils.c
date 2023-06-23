/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:26:03 by snaji             #+#    #+#             */
/*   Updated: 2023/06/23 20:20:47 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_data *data)
{
	free(data->philos);
	sem_close(data->forks);
	sem_close(data->printf);
	sem_close(data->simulation_ended);
	sem_close(data->nb_finish_eat);
	sem_close(data->eat_time);
	sem_unlink("/forks");
	sem_unlink("/printf");
	sem_unlink("/sim_ended");
	sem_unlink("/nb_finish_eat");
	sem_unlink("/eat_time");
}

void	kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		kill(data->philos[i++].pid, SIGKILL);
}

/* get the time passed since time was set with gettimeofday */
size_t	time_passed(struct timeval time)
{
	size_t			time_ms;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		pthread_exit(NULL);
	time_ms = (current_time.tv_sec * 1000000 + current_time.tv_usec)
		- (time.tv_sec * 1000000 + time.tv_usec);
	return (time_ms);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\v')
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str)
		result = result * 10 + *str++ - '0';
	return (sign * result);
}

size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}
