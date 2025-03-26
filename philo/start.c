/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/26 10:57:57 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	assign_values(t_info *info, t_phi *phi, int ind)
{
	phi->id = ind + 1;
	phi->info = info;
	if (ind == 0)
	{
		phi->l_fork = &phi->info->forks[ind - 1];
		phi->r_fork = &phi->info->forks[ind];
	}
	else
	{
		phi->l_fork = &phi->info->forks[phi->info->philo_count - 1];
		phi->r_fork = &phi->info->forks[0];
	}
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
	ind = -1;
	while (++ind < info->philo_count)
		if (pthread_create(&info->philos[ind].thr, NULL, routine, &info->philos[ind]) != 0)
			return (1);
	ind = -1;
	while (++ind < info->philo_count)
		pthread_join(info->philos[ind].thr, NULL);
	return (0);
}

static int	init_forks(t_info *info)
{
	int	ind;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (!info->forks)
		return (1);
	ind = -1;
	while (++ind < info->philo_count)
		pthread_mutex_init(&info->forks[ind], NULL);
	return (0);
}

int	start(int ac, char **av)
{
	t_info	info;

	ft_atoi(av[1], (int *)&info.philo_count);
	ft_atoi(av[2], (int *)&info.time_to_die);
	ft_atoi(av[3], (int *)&info.time_to_eat);
	ft_atoi(av[4], (int *)&info.time_to_sleep);
	info.must_eat = -1;
	if (ac == 6)
		ft_atoi(av[5], &info.must_eat);
	if (gettimeofday(&info.tv, NULL) == 0)
		info.time_init = (long long)info.tv.tv_sec * 1000 +\
	info.tv.tv_usec / 1000;
	//printf("\n%d, %d, %d, %d\n", (int)info.time_to_die, (int)info.time_to_eat, (int)info.time_to_sleep, info.must_eat);
	//printf("init time?: %lu\n", info.time_init);
	if (init_forks(&info) != 0)
		return (1);
	if (init_philos(&info) != 0)
		return (1);
	//free_all(info);
	return (0);
}
