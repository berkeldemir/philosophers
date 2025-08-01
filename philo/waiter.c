/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/15 15:49:14 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	died(t_phi *phi)
{
	if (pthread_mutex_lock(&phi->info->write_lock))
		return ;
	printf("%lu\t%i %s\n", elapsed_time(phi->info), phi->id, MSG_DIED);
	pthread_mutex_unlock(&phi->info->write_lock);
	pthread_mutex_lock(&phi->info->quit_lock);
	phi->info->quit = TRUE;
	pthread_mutex_unlock(&phi->info->quit_lock);
}

static int	check_meals_deads(t_info *info)
{
	int			i;
	int			philo_eat_count;
	int			total_ate;
	uint64_t	philo_last_meal;
	uint64_t	current_time;

	i = 0;
	total_ate = 0;
	while (i < info->philo_count)
	{
		pthread_mutex_lock(&info->philos[i].meal_lock);
		philo_eat_count = info->philos[i].eat_count;
		philo_last_meal = info->philos[i].last_meal;
		current_time = elapsed_time(info);
		pthread_mutex_unlock(&info->philos[i].meal_lock);
		if (current_time - philo_last_meal > info->time_to_die )
			return (died(&info->philos[i]), 1);
		if (info->must_eat > 0 && philo_eat_count >= info->must_eat)
			total_ate += 1;
		i++;
	}
	if (total_ate == info->philo_count)
		return (1);
	return (0);
}

void	*waiter(void *ptr)
{
	t_info	*info;

	info = (t_info *)ptr;
	while (1)
	{
		if (check_meals_deads(info))
		{
			pthread_mutex_lock(&info->quit_lock);
			info->quit = TRUE;
			pthread_mutex_unlock(&info->quit_lock);
			break ;
		}
		usleep(200);
	}
	return (NULL);
}
