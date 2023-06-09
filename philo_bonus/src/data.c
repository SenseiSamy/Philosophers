/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:29:56 by snaji             #+#    #+#             */
/*   Updated: 2023/06/22 17:22:48 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*create_philos(int n)
{
	t_philo	*philos;

	philos = malloc(n * sizeof (t_philo));
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, n * sizeof (t_philo));
	return (philos);
}

static int	get_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] < '0' || value[i] > '9')
			return (-1);
		++i;
	}
	return (ft_atoi(value));
}

static int	check_values(t_data *data, int ac)
{
	if (data->number_of_philosophers <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| (ac == 6 && data->number_of_times_each_philosopher_must_eat < 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_sem(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/printf");
	sem_unlink("/sim_ended");
	sem_unlink("/nb_finish_eat");
	sem_unlink("/eat_time");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			data->number_of_philosophers);
	data->printf = sem_open("/printf", O_CREAT | O_EXCL, 0644, 1);
	data->simulation_ended = sem_open("/sim_ended", O_CREAT | O_EXCL, 0644, 0);
	data->nb_finish_eat = sem_open("/nb_finish_eat", O_CREAT | O_EXCL, 0644, 0);
	data->eat_time = sem_open("/eat_time", O_CREAT | O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->printf == SEM_FAILED
		|| data->simulation_ended == SEM_FAILED || data->nb_finish_eat
		== SEM_FAILED || data->eat_time == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_data(int ac, char **av, t_data *data)
{
	if (ac < 5)
		return (write(2, "philo: not enough argument\n", 27), EXIT_FAILURE);
	else if (ac > 6)
		return (write(2, "philo: too many arguments\n", 26), EXIT_FAILURE);
	data->number_of_philosophers = get_value(av[1]);
	data->time_to_die = get_value(av[2]);
	data->time_to_eat = get_value(av[3]);
	data->time_to_sleep = get_value(av[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = get_value(av[5]);
	if (check_values(data, ac) == EXIT_FAILURE)
		return (write(2, "philo: invalid argument\n", 24), EXIT_FAILURE);
	data->think_time = 1;
	if (gettimeofday(&data->init_time, NULL) == -1)
		return (write(2, "philo: initialization failed\n", 29), EXIT_FAILURE);
	data->philos = create_philos(data->number_of_philosophers);
	if (data->philos == NULL || init_sem(data) == EXIT_FAILURE)
		return (write(2, "philo: initialization failed\n", 29), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
