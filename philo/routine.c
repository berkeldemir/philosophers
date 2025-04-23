/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:02:41 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/23 23:26:54 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
#include "./philo.h"

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
