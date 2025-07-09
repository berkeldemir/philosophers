/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:01:33 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/09 13:35:04 by beldemir         ###   ########.fr       */
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

# define MSG_TAKENFORK "has taken a fork"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_EATING "is eating"
# define MSG_DIED "died"

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
	sem_t		*s_ate;
	sem_t		*s_quit;
	uint64_t	time_init;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			must_eat;
}	t_table;

uint64_t	get_curr(uint16_t time_init);
void		ph_sleep(uint64_t duration);

int		ft_atoi(const char *str, unsigned long *tab_num);
int		ft_strcmp(const char *s1, const char *s2);
void	*self_routine(void *arg);
void	exit_noleak(t_table *table);
int		ph_print(t_phi *phi, char *act);
void	routine(t_phi *phi);
void	dining(t_table *table);
#endif