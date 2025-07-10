/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/10 19:15:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	cleanup(t_info *info)
{
	int	i;

	i = -1;
	if (info->forks)
		while (++i < info->philo_count)
			pthread_mutex_destroy(&info->forks[i]);
	if (info->forks)
		free(info->forks);
	i = -1;
	if (info->philos)
		while (++i < info->philo_count)
			pthread_mutex_destroy(&info->philos[i].meal_lock);
	if (info->philos)
		free(info->philos);
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->quit_lock);
}

static void	assign_values(t_info *info, t_phi *phi, int ind)
{
	phi->id = ind + 1;
	phi->info = info;
	phi->eat_count = 0;
	phi->last_meal = 0;
	phi->l_fork = &info->forks[ind];
	phi->r_fork = &info->forks[(ind + 1) % info->philo_count];
	if (pthread_mutex_init(&phi->meal_lock, NULL) != 0)
		exit(66);
}

static int	init_philos(t_info *info)
{
	int	ind;

	info->philos = (t_phi *)malloc(sizeof(t_phi) * info->philo_count);
	if (!info->philos)
		return (1);
	ind = -1;
	while (++ind < info->philo_count)
		assign_values(info, &info->philos[ind], ind);
	if (pthread_create(&info->waiter, NULL, &waiter, info) != 0)
		return (cleanup(info), 1);
	ind = -1;
	while (++ind < info->philo_count)
		if (pthread_create(&info->philos[ind].thr, NULL, routine, \
		&info->philos[ind]) != 0)
			return (1);
	pthread_join(info->waiter, NULL);
	ind = -1;
	while (++ind < info->philo_count)
		pthread_join(info->philos[ind].thr, NULL);
	return (0);
}

static int	init_forks(t_info *info)
{
	int	ind;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
	info->philo_count);
	if (!info->forks)
		return (1);
	ind = -1;
	while (++ind < info->philo_count)
	{
		if (pthread_mutex_init(&info->forks[ind], NULL) != 0)
		{
			while (--ind >= 0)
				pthread_mutex_destroy(&info->forks[ind]);
			free(info->forks);
			info->forks = NULL;
			return (1);
		}
	}
	return (0);
}

int	start(int ac, char **av)
{
	t_info	info;

	init_start(ac, av, &info);
	if (pthread_mutex_init(&info.write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&info.quit_lock, NULL) != 0)
		return (pthread_mutex_destroy(&info.write_lock), 1);
	if (init_forks(&info) != 0)
		return (pthread_mutex_destroy(&info.write_lock), \
		pthread_mutex_destroy(&info.quit_lock), 1);
	info.time_init = get_current();
	if (init_philos(&info) != 0)
	{
		pthread_mutex_lock(&info.quit_lock);
		info.quit = TRUE;
		pthread_mutex_unlock(&info.quit_lock);
		pthread_join(info.waiter, NULL);
		return (cleanup(&info), 1);
	}
	cleanup(&info);
	return (0);
}
