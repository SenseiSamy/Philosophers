/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:03:30 by snaji             #+#    #+#             */
/*   Updated: 2023/05/31 20:47:51 by snaji            ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

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
	int				id;
	pid_t			pid;
	int				nb_eat;
	struct timeval	eat_time;
	t_state			state;
	pthread_t		thread;
	t_data			*data;
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
	sem_t			*forks;
	sem_t			*printf;
	int				simulation_ended;
	t_philo			*philos;
};

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */

int		init_data(int ac, char **av, t_data *data);
size_t	time_passed(struct timeval time);
void	check_death(t_philo *self, t_data *data);
void	free_all(t_data *data);
int		ft_atoi(char *str);
int		start_processes(t_data *data);
void	*thread_check_death(void *ptr);

#endif