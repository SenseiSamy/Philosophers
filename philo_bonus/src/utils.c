/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:26:03 by snaji             #+#    #+#             */
/*   Updated: 2023/06/01 18:01:52 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_data *data)
{
	free(data->philos);
	sem_close(data->forks);
	sem_close(data->printf);
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

void	check_death(t_philo *self, t_data *data)
{
	if (time_passed(self->eat_time) >= (size_t)(data->time_to_die * 1000))
	{
		sem_wait(data->printf);
		printf("%ld %d died\n", time_passed(data->init_time) / 1000,
			self->id + 1);
		free_all(data);
		exit(EXIT_SUCCESS);
	}
}

void	*thread_check_death(void *ptr)
{
	t_philo	*self;

	self = (t_philo *)ptr;
	while (1)
		check_death(self, self->data);
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
