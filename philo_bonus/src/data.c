/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:29:56 by snaji             #+#    #+#             */
/*   Updated: 2023/05/28 21:39:27 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*create_philos(int n)
{
	t_philo	*philos;
	int		i;

	philos = malloc(n * sizeof (t_philo));
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, n * sizeof (t_philo));
	return (philos);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (ac < 5)
		return (write(2, "philo: not enough argument", 26), EXIT_FAILURE);
	else if (ac > 6)
		return (write(2, "philo: too many arguments", 25), EXIT_FAILURE);
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	data->think_time = (data->time_to_die - (data->time_to_eat
		+ data->time_to_sleep)) / 2;
	if (gettimeofday(&data->init_time, NULL) == -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->printf, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->simulation_ended_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	sem_init(&data->semaphore, 1, 0);
	data->philos = create_philos(data->number_of_philosophers);
	if (data->philos == NULL)
		return (EXIT_FAILURE);
	return (data->simulation_ended = 0, EXIT_SUCCESS);
}
