/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/23 04:46:22 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	must_eat_done(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		if (info->philos[i].eat_count >= info->must_eat)
			return (1) ;
		i++;
	}
	return (0);
}

void	*waiter(void *ptr)
{
	t_info	*info;

	info = (t_info *)ptr;
	while (1)
	{
		if (info->quit == TRUE || \
		(info->must_eat != -1 && must_eat_done(info) != 0))
			break ;
	}
	return (NULL);
}
