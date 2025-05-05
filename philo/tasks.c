/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:56:51 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/25 20:52:47 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	action(t_phi *phi, char *action)
{
	if (pthread_mutex_lock(phi->info->write_lock) != 0)
		return (1);
	printf("%lu\t%i %s\n", elapsed_time(phi->info), phi->id, action);
	if (pthread_mutex_unlock(phi->info->write_lock) != 0)
		return (1);
	return (0);
}
/*
void	take_forks(t_phi *phi)
{
	if (action(phi, "has taken a fork"))
	{			
		if (pthread_mutex_lock(phi->l_fork) != 0)
				return ;
		if (action(phi, "has taken a fork"))
			if (pthread_mutex_lock(phi->r_fork) != 0)
				return ;
	}
}

void	eat(t_phi *phi)
{
	if (action(phi, "is eating"))
	{
		
	}
}

void	think(t_phi *phi)
{
	if (action(phi, "is thinking"))
	{
		
	}
}

void	sleep(t_phi *phi)
{
	if (action(phi, "is sleeping"))
	{
		
	}
}
*/