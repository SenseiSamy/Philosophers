/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:09:16 by snaji             #+#    #+#             */
/*   Updated: 2023/05/05 16:41:09 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup(t_philo *philo, int ac, char **av)
{
	if (ac < 5)
		return (write(2, "philo: not enough argument", 26), EXIT_FAILURE);
	else if (ac > 6)
		return (write(2, "philo: too many arguments", 25), EXIT_FAILURE);
	philo->number_of_philosophers = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->number_of_times_each_philosopher_must_eat = av[5];
	else
		philo->number_of_times_each_philosopher_must_eat = -1;
	return (EXIT_SUCCESS);
}