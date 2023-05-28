/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:42:38 by snaji             #+#    #+#             */
/*   Updated: 2023/05/28 18:56:13 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (init_data(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philos = create_philos(&data);
	start_threads(&data, philos);
	free_all(&data, philos);
	return (EXIT_SUCCESS);
}
