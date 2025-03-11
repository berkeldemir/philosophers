/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:39:54 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/11 19:34:15 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define DEFAULT "\033[0m"
# define RED "\033[38;2;220;80;80m"      // Soft Red
# define GREEN "\033[38;2;80;200;120m"   // Soft Green
# define BLUE "\033[38;2;100;150;255m"   // Soft Blue
# define ORANGE "\033[38;2;255;170;80m"  // Soft Orange
# define YELLOW "\033[38;2;255;225;120m" // Soft Yellow


typedef struct s_app
{
	struct timeval	tv;
	pthread_t		*philo;
	int				*philo_id;
	int				count;
	//int	philo_count;
}   t_app;

int		init(t_app *app);
void	*routine(void *arg);


// ACTIONS
void	taken_a_fork(int philo_id);
void	eating(int philo_id);
void	sleeping(int philo_id);
void	thinking(int philo_id);
void	died(int philo_id);

#endif