/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:55:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/22 19:21:54 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static void	one_philo(t_phi *phi)
{
	action(phi, MSG_TAKENFORK);
	ph_sleep(phi->info->time_to_die);
	action(phi, MSG_DIED);
	sem_post(phi->info->s_death);
}

void	routine(t_phi *phi)
{
	if (phi->info->philo_count == 1)
		return (one_philo(phi));
	if (phi->id % 2 == 0)
		ph_sleep(60);
	while (phi->info->must_eat == -1 || phi->eat_count < phi->info->must_eat)
	{
		action(phi, MSG_THINKING);
		sem_wait(phi->info->s_forks);
		action(phi, MSG_TAKENFORK);
		sem_wait(phi->info->s_forks);
		action(phi, MSG_TAKENFORK);
		action(phi, MSG_EATING);
		phi->eat_count++;
		phi->last_meal = elapsed_time(phi->info);
		ph_sleep(phi->info->time_to_eat);
		sem_post(phi->info->s_forks);
		sem_post(phi->info->s_forks);
		if (phi->info->must_eat != -1 && phi->eat_count >= phi->info->must_eat)
			break ;
		action(phi, MSG_SLEEPING);
		ph_sleep(phi->info->time_to_sleep);
	}
	if (phi->info->must_eat > 0)
		sem_post(phi->info->s_ate);
	sem_post(phi->info->s_done);
}
