/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:40:12 by snaji             #+#    #+#             */
/*   Updated: 2023/05/05 20:28:12 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*                                  INCLUDE                                   */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

/******************************************************************************/
/*                             STRUCT AND TYPEDEF                             */

typedef struct s_philo	t_philo;

struct s_philo
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int			*forks;
	pthread_t	*threads;
};

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */

int	setup(t_philo *philo, int ac, char **av);

int	ft_atoi(char *str);

#endif