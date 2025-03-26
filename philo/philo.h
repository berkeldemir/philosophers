/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:58:05 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/26 10:57:28 by beldemir         ###   ########.fr       */
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

struct s_info;

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING
}	t_status;

typedef struct s_phi
{
	pthread_t		thr;
	int				id;
	t_status		status;
	struct s_info	*info;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_phi;

typedef struct s_info
{
	struct s_phi	*philos;
	pthread_mutex_t	*forks;
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
int		start(int ac, char **av);
void	*routine(void *arg);

#endif