/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:25 by snaji             #+#    #+#             */
/*   Updated: 2023/05/28 18:56:21 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	sim_end(t_philo	*philo, t_data *data)
{
	bool	end;

	end = false;
	pthread_mutex_lock(&data->simulation_ended_mutex);
	if (data->simulation_ended == 1)
		end = true;
	else if (time_passed(philo->eat_time) >= (size_t)(data->time_to_die * 1000))
	{
		data->simulation_ended = 1;
		end = true;
		pthread_mutex_lock(&data->printf);
		printf("%ld %d died\n", time_passed(data->init_time) / 1000,
			philo->id + 1);
		pthread_mutex_unlock(&data->printf);
	}
	if (end == true)
		philo->state = dead;
	pthread_mutex_unlock(&data->simulation_ended_mutex);
	return (end);
}
