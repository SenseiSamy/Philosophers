/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:01:23 by snaji             #+#    #+#             */
/*   Updated: 2023/05/19 23:56:13 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philos(void)
{
	t_philo		*philos;
	const int	n = get_data()->number_of_philosophers;
	int			i;

	philos = malloc(n * sizeof (t_philo));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		philos[i].id = i;
		if (i == 0)
			philos[i].left_fork = n - 1;
		else
			philos[i].left_fork = i;
		if (i == n - 1)
			philos[i].right_fork = 0;
		else
			philos[i].right_fork = i + 1;
		philos[i].state = thinking;
		++i;
	}
	return (philos);
}

int	start_threads(t_philo *philos)
{
	const int	n = get_data()->number_of_philosophers;
	int			i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]))
			return (EXIT_FAILURE);
		usleep(5);
		++i;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
