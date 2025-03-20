/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:01:39 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 15:30:22 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ask_waiter(t_philo *philo, t_app *app)
{
	int i;

	i = 0;
	if (pthread_mutex_trylock(philo->l_fork) != 0 || \
	pthread_mutex_trylock(philo->r_fork) != 0)
		return (0);
	while (i < app->philo_count)
	{
		if (philo->last_eaten > app->philos[i].last_eaten)
			return (0);
		i++;
	}
	return (1);
}
