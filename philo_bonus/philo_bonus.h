/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:33:20 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/22 22:01:43 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>

# define MAX_PHILO 200

# define MSG_TAKENFORK "has taken a fork"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_EATING "is eating"
# define MSG_DIED "died"

struct	s_info;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_phi
{
	int				id;
	int				eat_count;
	uint64_t		last_meal;
	pthread_t		self_monitor;
	struct s_info	*info;
}	t_phi;

typedef struct s_info
{
	pid_t			*pids;
	sem_t			*s_forks;
	sem_t			*s_write;
	sem_t			*s_death;
	sem_t			*s_ate;
	sem_t			*s_done;
	t_bool			done;
	pthread_t		watcher;
	struct s_phi	philo;
	int				philo_count;
	uint64_t		time_init;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat;
}	t_info;

void		cleanup(t_info *info);
int			ft_atoi(const char *str, unsigned long *tab_num);
void		ph_sleep(uint64_t duration);
void		init_start(int ac, char **av, t_info *info);
int			start(int ac, char **av);
t_bool		dead_end(t_phi *phi);
int			action(t_phi *phi, char *action);
void		*waiter(void *ptr);
void		routine(t_phi *phi);
uint64_t	get_current(void);
uint64_t	elapsed_time(t_info	*info);

#endif