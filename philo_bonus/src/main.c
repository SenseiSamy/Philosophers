/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:19:22 by snaji             #+#    #+#             */
/*   Updated: 2023/06/22 16:29:25 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(ac, av, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_processes(&data) == EXIT_FAILURE)
		return (write(2, "philo: error during execution\n", 30), EXIT_FAILURE);
	free_all(&data);
	return (EXIT_SUCCESS);
}
