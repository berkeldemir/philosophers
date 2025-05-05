/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/05 15:28:54 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	died(t_phi *phi)
{
	if (pthread_mutex_lock(&phi->info->write_lock))
		return ;
	printf("%lu\t%i %s\n", elapsed_time(phi->info), phi->id, MSG_DIED);
	pthread_mutex_unlock(&phi->info->write_lock);
}

static int	must_eat_done(t_info *info)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_lock(&info->philos[i].meal_lock);
		if (info->philos[i].eat_count >= info->must_eat)
			done++;
		pthread_mutex_unlock(&info->philos[i].meal_lock);
		i++;
	}
	if (done == info->philo_count)
		return (1);
	return (0);
}

static int	anyone_starving(t_info *info)
{
	int	i;
	
	i = 0;
	while (i < info->philo_count)
	{
		if (elapsed_time(info) - info->philos[i].last_meal > info->time_to_die)
		{
			died(&info->philos[i]);
			info->quit = TRUE;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*waiter(void *ptr)
{
	t_info	*info;

	info = (t_info *)ptr;
	while (1)
	{
		if (info->quit == TRUE || \
		(info->must_eat >= 0 && must_eat_done(info) != 0) || \
		anyone_starving(info) != 0)
			break ;
	}
	return (NULL);
}
