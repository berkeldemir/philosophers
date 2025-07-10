/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:45:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/10 20:05:22 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

uint64_t	get_curr(uint64_t time_init)
{
	struct timeval	tv;
	uint64_t		curr;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	curr = ((uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
	curr = curr - time_init;
	return (curr);
}

void	ph_sleep(uint64_t duration)
{
	uint64_t	start;

	start = get_curr(0);
	while ((get_curr(0) - start) < duration)
		usleep(100);
}

int		ph_print(t_phi *phi, char *act)
{	
	uint64_t		curr;
	int				i;
	
	if (phi->ate == phi->table->must_eat)
		return (-1);
	curr = get_curr(phi->table->time_init);
	if (!curr)
		return (-1);
	sem_wait(phi->table->s_print);
	printf("%lu\t%i %s\n", curr, phi->id, act);
	if (!ft_strcmp(act, MSG_DIED))
	{
		i = -1;
		while (++i < phi->table->philo_count)
			sem_post(phi->table->s_ate);
		return (-1);
	}
	sem_post(phi->table->s_print);
	return (0);
}

void	*exit_check(void *arg)
{
	t_phi	*phi;
	
	phi = (t_phi *)arg;
	pthread_detach(phi->exitcheck);
	sem_wait(phi->table->s_quit);
	printf("%d %d\n", phi->id, phi->ate);
	exit_noleak(phi->table);
	return (NULL);
}

void	*self_control(void *arg)
{
	t_phi	*phi;
	
	phi = (t_phi *)arg;
	pthread_detach(phi->self);
	while (1)
	{
		if (get_curr(phi->table->time_init) - phi->last_meal > phi->table->time_to_die)
			if (ph_print(phi, MSG_DIED))
				break ;
		usleep(100);
	}
	exit_noleak(phi->table);
	return (NULL);
}

void	routine(t_phi *phi)
{
	sem_wait(phi->table->s_start);
	if (phi->id % 2 == 1)
		usleep(60000);
	while (1)
	{
		sem_wait(phi->table->s_forks);
		printf("%d started\n", phi->id);
		if (ph_print(phi, MSG_TAKENFORK))
			break ;
		sem_wait(phi->table->s_forks);
		if (ph_print(phi, MSG_TAKENFORK))
			break ;
		if (ph_print(phi, MSG_EATING))
			break ;
		phi->ate++;
		phi->last_meal = get_curr(phi->table->time_init);
		ph_sleep(phi->table->time_to_eat);
		(sem_post(phi->table->s_forks), sem_post(phi->table->s_forks));
		if (ph_print(phi, MSG_SLEEPING))
			break ;
		ph_sleep(phi->table->time_to_sleep);
		if (ph_print(phi, MSG_THINKING))
			break ;
	}
	sem_post(phi->table->s_ate);
	exit_noleak(phi->table);
}

void	dining(t_table *table)
{
	int	i;

	i = -1;
	while (++i <= table->philo_count)
		sem_post(table->s_start);
	i = -1;
	while (++i < table->philo_count)
		sem_wait(table->s_ate);
	i = -1;
	while (++i < table->philo_count)
		sem_post(table->s_quit);
	exit_noleak(table);
}