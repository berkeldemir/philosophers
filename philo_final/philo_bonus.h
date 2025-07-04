/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:01:33 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/04 15:01:34 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>

typedef enum e_bool		t_bool;
typedef struct s_phi	t_phi;
typedef struct s_table	t_table;

typedef enum e_bool
{
    FALSE = 0,
    TRUE = 1
}	t_bool;

typedef struct s_phi
{
	int			id;
	uint64_t	last_meal;
	int			ate;
	pthread_t	self;
	t_table		*table;
}	t_phi;

typedef struct s_table
{
	int			philo_count;
	pid_t		*pids;
	t_phi		*phis;
	sem_t		*s_start;
	sem_t		*s_forks;
	sem_t		*s_print;
	sem_t		*s_read;
	t_bool		quit;
	uint64_t	time_init;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			must_eat;
	int			total_ate;
}	t_table;



#endif