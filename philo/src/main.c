/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:42:38 by snaji             #+#    #+#             */
/*   Updated: 2023/05/20 01:09:20 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (init_data(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philos = create_philos();
	start_threads(philos);
	print_forks();
	return (EXIT_SUCCESS);
}
