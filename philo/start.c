/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/23 04:40:50 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

uint64_t	elapsed_time(t_info	*info)
{
	if (!info->time_init)
	{
		if (gettimeofday(&info->tv, NULL) == 0)
			info->time_init = (uint64_t)info->tv.tv_sec * 1000 + \
			(uint64_t)info->tv.tv_usec / 1000;
		else
			return ((uint64_t)-1);
		return (0);
	}
	else
	{
		if (gettimeofday(&info->tv, NULL) == 0)
			return ((uint64_t)info->tv.tv_sec * 1000 + \
			(uint64_t)info->tv.tv_usec / 1000 - info->time_init);
		else
			return ((uint64_t)-1);
	}
}

static void	assign_values(t_info *info, t_phi *phi, int ind)
{
	phi->id = ind + 1;
	phi->info = info;
	phi->eat_count = 0;
	phi->last_meal = 0;
	phi->l_fork = &info->forks[ind];
	phi->r_fork = &info->forks[(ind + 1) % info->philo_count];
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
	pthread_join(*info->waiter, NULL);
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
		if (pthread_mutex_init(&info->forks[ind], NULL) != 0)
			return (1);
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
	if (elapsed_time(&info) != 0)
		return (1);
	//printf("\n%d, %d, %d, %d\n", (int)info.time_to_die, (int)info.time_to_eat, (int)info.time_to_sleep, info.must_eat);
	//printf("init time?: %lu\n", info.time_init);
	if (pthread_create(info.waiter, NULL, &waiter, &info) != 0)
		return (1);
	if (init_forks(&info) != 0)
		return (1);
	if (init_philos(&info) != 0)
		return (1);
	return (0);
}
