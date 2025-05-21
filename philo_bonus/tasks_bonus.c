/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:14:30 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/21 17:37:50 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

uint64_t	get_current(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return ((uint64_t)(-1));
	return ((uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
}

uint64_t	elapsed_time(t_info	*info)
{
	return (get_current() - info->time_init);
}


int	action(t_phi *phi, char *action)
{
	sem_wait(phi->info->s_write);
	printf("%lu\t%i %s\n", elapsed_time(phi->info), phi->id, action);
	if (action[0] != 'd')
		sem_post(phi->info->s_write);
	return (0);
}