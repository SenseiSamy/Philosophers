/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:01:23 by snaji             #+#    #+#             */
/*   Updated: 2023/05/11 15:51:07 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int n)
{
	t_philo	*philos;
	int		i;

	philos = malloc(n * sizeof (t_philo));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < n + 1)
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
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (setup(&philo, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}
