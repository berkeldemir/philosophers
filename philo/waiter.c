/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/24 05:57:10 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	died(t_phi *phi)
{
	if (action(phi, "died"))
	{
		
	}
}

static int	must_eat_done(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		if (info->philos[i].eat_count >= info->must_eat)
			return (1);
		i++;
	}
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
			died(info->philos[i]);
			info->quit = TRUE;
		}
		i++;
	}
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
