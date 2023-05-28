/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 00:20:49 by snaji             #+#    #+#             */
/*   Updated: 2023/05/28 19:46:49 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	mutex_fork_equal(t_fork *fork, int value)
{
	bool	result;

	pthread_mutex_lock(&fork->mutex);
	if (fork->fork == value)
		result = true;
	else
		result = false;
	pthread_mutex_unlock(&fork->mutex);
	return (result);
}

void	mutex_fork_assign(t_fork *fork, int value)
{
	pthread_mutex_lock(&fork->mutex);
	fork->fork = value;
	pthread_mutex_unlock(&fork->mutex);
}
