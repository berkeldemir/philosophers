/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:01:39 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 19:25:51 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ask_waiter(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

	while (pthread_mutex_trylock(philo->l_fork) != 0 || \
	pthread_mutex_trylock(philo->r_fork) != 0)
	{
		if (philo->philo_id % 2 == 0)
		{
			first_fork = philo->l_fork;
			second_fork = philo->r_fork;
		}
		else
		{
			first_fork = philo->r_fork;
			second_fork = philo->l_fork;
		}
		if (pthread_mutex_trylock(first_fork) != 0)
			return (0);
		if (pthread_mutex_trylock(second_fork) != 0)
		{
			pthread_mutex_unlock(first_fork);
			return (0);
		}
	}
	return (1);
}
