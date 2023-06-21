/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:19:22 by snaji             #+#    #+#             */
/*   Updated: 2023/06/21 21:05:30 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_processes(&data);
	free_all(&data);
	sem_unlink("/forks");
	sem_unlink("/printf");
	sem_unlink("/sim_ended");
	sem_unlink("nb_finish_eat");
}
