/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:24:52 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/05 16:58:38 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	assign_values(t_info *info, t_phi *phi, int ind)
{
	phi->id = ind + 1;
	phi->info = info;
	phi->eat_count = 0;
	phi->last_meal = 0;
	phi->l_fork = &info->forks[ind];
	phi->r_fork = &info->forks[(ind + 1) % info->philo_count];
	pthread_mutex_init(&phi->meal_lock, NULL);
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
		if (pthread_create(&info->philos[ind].thr, NULL, routine, \
		&info->philos[ind]) != 0)
			return (1);
	pthread_join(info->waiter, NULL);
	ind = -1;
	while (++ind < info->philo_count)
		pthread_join(info->philos[ind].thr, NULL); // Still problematic logic, see note below
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
	if (pthread_mutex_init(&info.write_lock, NULL) != 0)
		return (1);
	if (init_forks(&info) != 0)
		return (1);
	info.quit = FALSE;
	info.time_init = get_current();
	if (pthread_create(&info.waiter, NULL, &waiter, &info) != 0)
		return (1);
	if (init_philos(&info) != 0)
		return (1);
	return (0);
}
