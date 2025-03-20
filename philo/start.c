/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 14:25:40 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	*inner_routine(t_philo *philo, t_app *app)
{
	if (ask_waiter(philo, app))
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		philo->meals_had++;
		//philo->last_eaten(app->start - );
		eating(app->start, philo->philo_id);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

static void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->app->quit != 1)
	{
		/*
		if (inner_routine(philo, philo->app))
		*/
	}
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
	app->philos[0].l_fork = &app->forks[app->philo_count - 1];
	app->philos[0].r_fork = &app->forks[0];
	i = -1;
	while (++i < app->philo_count)
	{
		app->philos[i].philo_id = i + 1;
		app->philos[i].stat = THINKING;
		app->philos[i].full = FALSE;
		app->philos[i].meals_had = 0;
		app->philos[i].last_eaten = 0;
		app->philos[i].app = app;
		if (i != 0)
			app->philos[i].l_fork = &app->forks[i - 1];
		if (i != 0)
			app->philos[i].r_fork = &app->forks[i];
		pthread_create(&app->philos[i].thread, NULL, routine, (void *)&app);
	}
	i = -1;
	while (++i < app->philo_count)
		pthread_join(app->philos[i].thread, NULL);
	return (0);
}

int	start(t_app *app)
{
	int	i;

	app->forks = (t_fork *)malloc(sizeof(t_fork) * app->philo_count);
	if (!app->forks)
		return (1);
	i = -1;
	while (++i < app->philo_count)
	{
		pthread_mutex_init(&app->forks[i].fork, NULL);
		app->forks[i].fork_id = i + 1;
	}
	if (start_philos(app) != 0)
		return (1);
	return (0);
}
