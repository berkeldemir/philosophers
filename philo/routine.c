/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:02:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/08/01 17:48:22 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_bool	dead_end(t_phi *phi)
{
	t_bool	stop;

	pthread_mutex_lock(&phi->info->quit_lock);
	stop = phi->info->quit;
	pthread_mutex_unlock(&phi->info->quit_lock);
	return (stop);
}

static int	lock_both_forks(t_phi *phi)
{
	if (phi->id % 2 == 1)
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

static int	ph_routine(t_phi *phi)
{
	if (phi->id % 2 == 0)
		ph_sleep(phi->info->time_to_eat);
	else if (phi->id == phi->info->philo_count && phi->id % 2 == 1)
		ph_sleep(2 * phi->info->time_to_eat);
	else
		usleep(100);
	while (dead_end(phi) == FALSE)
	{
		if (phi->info->must_eat == -1 || phi->eat_count < phi->info->must_eat)
			if (lock_both_forks(phi) != 0)
				return (1);
		pthread_mutex_lock(&phi->meal_lock);
		if (phi->info->must_eat == -1 || phi->eat_count < phi->info->must_eat)
			action(phi, MSG_EATING);
		phi->eat_count += 1;
		phi->last_meal = elapsed_time(phi->info);
		pthread_mutex_unlock(&phi->meal_lock);
		ph_sleep(phi->info->time_to_eat);
		if (pthread_mutex_unlock(phi->r_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(phi->l_fork) != 0)
			return (1);
		action(phi, MSG_SLEEPING);
		ph_sleep(phi->info->time_to_sleep);
		action(phi, MSG_THINKING);
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
		ph_sleep(phi->info->time_to_die);
	}
	else
		ph_routine(phi);
	return (NULL);
}
