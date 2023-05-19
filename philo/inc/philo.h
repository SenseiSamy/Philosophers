/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaji <snaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:40:12 by snaji             #+#    #+#             */
/*   Updated: 2023/05/19 23:41:08 by snaji            ###   ########.fr       */
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
# include <sys/time.h>

/******************************************************************************/
/*                             STRUCT AND TYPEDEF                             */

typedef enum e_state	t_state;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

enum e_state
{
	sleeping,
	eating,
	thinking,
	dead
};

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
	t_state		state;
	pthread_t	thread;
};

struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct timeval	init_time;
	t_fork			*forks;
};

/******************************************************************************/
/*                            FUNCTION DECLARATION                            */

t_data	*get_data(void);
int		init_data(int ac, char **av);
t_philo	*create_philos(void);
int		start_threads(t_philo *philos);
void	*philo_routine(void *ptr);
void	fork_change_value(t_fork *fork, int value);
int		ft_atoi(char *str);
size_t	time_passed(struct timeval time);

#endif