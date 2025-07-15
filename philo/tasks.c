/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:56:51 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/15 15:52:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
	if (dead_end(phi))
		return (-1);
	if (pthread_mutex_lock(&phi->info->write_lock) != 0)
		return (-1);
	printf("%lu\t%i %s\n", elapsed_time(phi->info), phi->id, action);
	if (pthread_mutex_unlock(&phi->info->write_lock) != 0)
		return (-1);
	return (0);
}
