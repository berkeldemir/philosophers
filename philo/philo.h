/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:58:05 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/23 04:48:45 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO 200

struct s_info;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_phi
{
	pthread_t		thr;
	int				id;
	int				eat_count;
	uint64_t		last_meal;
	struct s_info	*info;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_phi;

typedef struct s_info
{
	struct s_phi	*philos;
	pthread_mutex_t	*forks;
	pthread_t		*waiter;
	int				philo_count;
	struct timeval	tv;
	uint64_t		time_init;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat;
	t_bool			quit;
}	t_info;

int		ft_atoi(const char *str, int *tab_num);

int			start(int ac, char **av);
void		*waiter(void *ptr);
void		*routine(void *arg);
uint64_t	elapsed_time(t_info	*info);

#endif