/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:54:51 by snaji             #+#    #+#             */
/*   Updated: 2023/05/19 23:32:55 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

static t_fork	*create_forks(void)
{
	t_fork		*forks;
	const int	n = get_data()->number_of_philosophers;
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

int	init_data(int ac, char **av)
{
	t_data	*data;

	data = get_data();
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
	if (gettimeofday(&data->init_time, NULL) == -1)
		return (EXIT_FAILURE);
	data->forks = create_forks();
	if (data->forks == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
