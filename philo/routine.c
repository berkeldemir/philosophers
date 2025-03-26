/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:02:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/26 11:04:42 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include "./philo.h"

int check_alive(t_phi *phi)
{

}

int check_must_eat_done(t_phi *phi)
{
	
}

void	*waiter(void *arg)
{

}

void	*routine(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	pthread_mutex_lock(&phi->info->forks[0]);
	printf("id:%i\n", phi->id);
	pthread_mutex_unlock(&phi->info->forks[0]);
	phi->l_fork = NULL;
	return (NULL);
}
