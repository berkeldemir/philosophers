/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:13:21 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/15 16:33:53 by beldemir         ###   ########.fr       */
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

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	uint64_t		last_eat;
	pthread_t		thread;
	pthread_mutex_t	read_lock;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_bool			is_dead;
	struct s_info	info;
}	t_philo;

typedef struct s_info
{
	t_philo			*phi;
	int				philo_count;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	read_lock;
	uint64_t		time2die;
	uint64_t		time2eat;
	uint64_t		time2sleep;
	int				must_eat;
}	t_info;

#endif