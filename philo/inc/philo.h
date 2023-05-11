/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:40:12 by snaji             #+#    #+#             */
/*   Updated: 2023/05/10 19:53:13 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*                                  INCLUDE                                   */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

/******************************************************************************/
/*                             STRUCT AND TYPEDEF                             */

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_fork
{
	int				fork;
	pthread_mutex_t	mutex;
};

struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	pthread_t	thread;
};

struct s_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	t_fork		*forks;
};

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */

int	setup(t_philo *philo, int ac, char **av);

int	ft_atoi(char *str);

#endif