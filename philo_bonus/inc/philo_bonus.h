/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:03:30 by snaji             #+#    #+#             */
/*   Updated: 2023/05/28 21:49:28 by snaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/******************************************************************************/
/*                                  INCLUDE                                   */
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>

/******************************************************************************/
/*                             STRUCT AND TYPEDEF                             */

typedef enum e_state	t_state;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

enum e_state
{
	sleeping,
	eating,
	thinking,
	dead
};

struct s_philo
{
	pid_t			pid;
	int				nb_eat;
	struct timeval	eat_time;
	t_state			state;
};

struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				think_time;
	struct timeval	init_time;
	sem_t			semaphore;
	pthread_mutex_t	printf;
	pthread_mutex_t	simulation_ended_mutex;
	int				simulation_ended;
	t_philo			*philos;
};

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */

int	init_data(int ac, char **av, t_data *data);

#endif