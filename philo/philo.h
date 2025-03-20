/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:39:54 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 14:22:14 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>

# define DEFAULT "\033[0m"
# define RED "\033[38;2;220;80;80m"      // Soft Red
# define GREEN "\033[38;2;80;200;120m"   // Soft Green
# define BLUE "\033[38;2;100;150;255m"   // Soft Blue
# define ORANGE "\033[38;2;255;170;80m"  // Soft Orange
# define YELLOW "\033[38;2;255;225;120m" // Soft Yellow
# define PURPLE "\033[38;2;180;130;255m"  // Soft Purple

struct	s_app;

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef enum e_stat
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3
}	t_stat;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	unsigned int	fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	t_stat			stat;
	t_bool			full;
	int				meals_had;
	uint64_t		last_eaten;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct s_app	*app;
}	t_philo;

typedef struct s_app
{
	t_fork			*forks;
	t_philo			*philos;
	int				philo_count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_slp;
	int				max_meal;
	uint64_t		start;
	t_bool			quit;
}	t_app;

int			start(t_app *app);

// Time Functions
uint64_t	get_time(void);
void		elapsed_time(uint64_t init_time);

// Actions
void		taken_a_fork(int start, int philo_id);
void		eating(int start, int philo_id);
void		sleeping(int start, int philo_id);
void		thinking(int start, int philo_id);
void		died(int start, int philo_id);

// Utils
int			ft_isnum(char *str);
int			ft_atoi(char *str);

#endif