/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:02:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/05 21:15:12 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static t_bool	dead_end(t_phi *phi)
{
	t_bool	stop;

	pthread_mutex_lock(&phi->info->quit_lock);
	stop = phi->info->quit;
	pthread_mutex_unlock(&phi->info->quit_lock);
	return (stop);
}

static int	lock_both_forks(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		if (pthread_mutex_lock(phi->r_fork) != 0)
			return (1);
		action(phi, MSG_TAKENFORK);
		if (pthread_mutex_lock(phi->l_fork) != 0)
			return (pthread_mutex_unlock(phi->r_fork), 1);
		action(phi, MSG_TAKENFORK);
		return (0);
	}
	else
	{
		if (pthread_mutex_lock(phi->l_fork) != 0)
			return (1);
		action(phi, MSG_TAKENFORK);
		if (pthread_mutex_lock(phi->r_fork) != 0)
			return (pthread_mutex_unlock(phi->l_fork), 1);
		action(phi, MSG_TAKENFORK);
		return (0);
	}
}

static int	ft_routine(t_phi *phi)
{
	if (phi->id % 2 == 0)
		usleep(phi->info->time_to_eat * 1000);
	while (dead_end(phi) == FALSE)
	{
		action(phi, MSG_THINKING);
		if (lock_both_forks(phi) != 0)
			return (1);
		pthread_mutex_lock(&phi->meal_lock);
		action(phi, MSG_EATING);
		phi->last_meal = elapsed_time(phi->info);
		phi->eat_count++;
		pthread_mutex_unlock(&phi->meal_lock);
		usleep(phi->info->time_to_eat * 1000);
		if (pthread_mutex_unlock(phi->r_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(phi->l_fork) != 0)
			return (1);
		action(phi, MSG_SLEEPING);
		usleep(phi->info->time_to_sleep * 1000);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	pthread_mutex_lock(&phi->meal_lock);
	phi->last_meal = elapsed_time(phi->info);
	pthread_mutex_unlock(&phi->meal_lock);
	if (phi->info->philo_count == 1)
	{
		action(phi, MSG_TAKENFORK);
		usleep(phi->info->time_to_die * 1000);
	}
	else
		ft_routine(phi);
	return (NULL);
}
