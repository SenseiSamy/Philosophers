/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:20:49 by snaji             #+#    #+#             */
/*   Updated: 2023/05/20 01:36:35 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_fork_equal(t_fork *fork, int value)
{
	int	result;

	pthread_mutex_lock(&fork->mutex);
	result = fork->fork == value;
	pthread_mutex_unlock(&fork->mutex);
	return (result);
}

void	mutex_fork_assign(t_fork *fork, int value)
{
	pthread_mutex_lock(&fork->mutex);
	fork->fork = value;
	pthread_mutex_unlock(&fork->mutex);
}
