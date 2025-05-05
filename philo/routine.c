/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:02:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/05 17:15:55 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	lock_both_forks(t_phi *phi)
{
	if (pthread_mutex_lock(phi->l_fork) != 0)
		return (1);
	action(phi, MSG_TAKENFORK);
	if (pthread_mutex_lock(phi->r_fork) != 0)
	{
		pthread_mutex_unlock(phi->l_fork);
		return (1);
	}
	action(phi, MSG_TAKENFORK);
	return (0);
}

static int	even_routine(t_phi *phi)
{
	if (phi->id % 2 == 0)
	{
		action(phi, MSG_THINKING);
		usleep(phi->info->time_to_eat * 1000);
	}
	while (1)
	{
		if (lock_both_forks(phi) != 0)
			return (1);
		action(phi, MSG_EATING);
		phi->last_meal = elapsed_time(phi->info);
		usleep(phi->info->time_to_eat * 1000);
		if (pthread_mutex_unlock(phi->r_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(phi->l_fork) != 0)
			return (1);
		action(phi, MSG_SLEEPING);
		usleep(phi->info->time_to_sleep * 1000);
		action(phi, MSG_THINKING);
	}
}
/*
static int	odd_routine(t_phi *phi)
{
	
}
*/
void	*routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	if (phi->info->philo_count % 2 == 0)
		even_routine(phi);
	else
		even_routine(phi);
	return (NULL);
}
