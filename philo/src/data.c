/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:54:51 by snaji             #+#    #+#             */
/*   Updated: 2023/05/29 19:27:30 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*create_forks(t_data *data)
{
	t_fork		*forks;
	const int	n = data->number_of_philosophers;
	int			i;

	forks = malloc(n * sizeof (t_fork));
	i = 0;
	while (i < n)
	{
		forks[i].fork = -1;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
			return (NULL);
		++i;
	}
	return (forks);
}

static int	check_values(t_data *data)
{
	if (data->number_of_philosophers <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (ac < 5)
		return (write(2, "philo: not enough argument\n", 27), EXIT_FAILURE);
	else if (ac > 6)
		return (write(2, "philo: too many arguments\n", 26), EXIT_FAILURE);
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (check_values(data) == EXIT_FAILURE)
		return (write(2, "philo: invalid argument\n", 24), EXIT_FAILURE);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	data->think_time = (data->time_to_die - (data->time_to_eat
		+ data->time_to_sleep)) / 2;
	if (gettimeofday(&data->init_time, NULL) == -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->printf, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&data->simulation_ended_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	data->forks = create_forks(data);
	if (data->forks == NULL)
		return (EXIT_FAILURE);
	return (data->simulation_ended = 0, EXIT_SUCCESS);
}

void	free_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i++].mutex);
	pthread_mutex_destroy(&data->printf);
	free(data->forks);
	free(philos);
}
