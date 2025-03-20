/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 19:25:16 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	inner_routine(t_philo *philo, t_app *app)
{
	thinking(app->start, philo->philo_id);
	while (ask_waiter(philo) == 0)
	{
		if (get_time() - philo->last_eaten >= app->time_to_die)
		{
			died(app->start, philo->philo_id);
			app->quit = TRUE;
			return ;
		}
		if (app->quit == TRUE)
			return ;
	}
	if (philo->philo_id == 1) // Check if it's the first philosopher
	{
		pthread_mutex_lock(philo->r_fork);
		taken_a_fork(app->start, philo->philo_id);
		pthread_mutex_lock(philo->l_fork);
		taken_a_fork(app->start, philo->philo_id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		taken_a_fork(app->start, philo->philo_id);
		pthread_mutex_lock(philo->r_fork);
		taken_a_fork(app->start, philo->philo_id);
	}
	philo->meals_had++;
	philo->last_eaten = get_time();
	eating(app->start, philo->philo_id);
	usleep(app->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	sleeping(app->start, philo->philo_id);
	usleep(app->time_to_slp * 1000);
}

static void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	inner_routine(philo, philo->app);
	if (!philo->app)
		return (NULL);
	return (NULL);
}

int	start_philos(t_app *app)
{	
	int	i;

	app->philos = (t_philo *)malloc(sizeof(t_philo) * app->philo_count);
	if (!app->philos)
		return (1);
	init_philo(app, 0);
	app->philos[0].l_fork = &app->forks[app->philo_count - 1];
	app->philos[0].r_fork = &app->forks[0];
	i = 0;
	while (++i < app->philo_count)
	{
		init_philo(app, i);
		//printf("philo %i initiliazed, their id: %i\n", i, app->philos[i].philo_id);
		app->philos[i].l_fork = &app->forks[i - 1];
		app->philos[i].r_fork = &app->forks[i];
		pthread_create(&app->philos[i].thread, NULL, routine, (void *)&app->philos[i]);
	}
	i = -1;
	while (++i < app->philo_count)
		pthread_join(app->philos[i].thread, NULL);
	return (0);
}

int	start(t_app *app)
{
	int	i;

	app->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * app->philo_count);
	if (!app->forks)
		return (1);
	i = -1;
	while (++i < app->philo_count)
		pthread_mutex_init(&app->forks[i], NULL);
	if (start_philos(app) != 0)
		return (1);
	return (0);
}
