/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 15:34:24 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	inner_routine(t_philo *philo, t_app *app)
{
	thinking(app->start, philo->philo_id);
	while (ask_waiter(philo, app) == 0)
		if (philo->last_eaten - app->start >= app->time_to_die)
			return (died(app->start, philo->philo_id));
	usleep(app->time_to_die * 100);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	taken_a_fork(app->start, philo->philo_id);
	taken_a_fork(app->start, philo->philo_id);
	philo->meals_had++;
	philo->last_eaten = get_time() - app->start;
	eating(app->start, philo->philo_id);
	usleep(app->time_to_eat * 100);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	sleeping(app->start, philo->philo_id);
	usleep(app->time_to_slp * 100);
}

static void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (1)//should_close(philo->app) != 1)
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
	app->philos[0].l_fork = &app->forks[app->philo_count - 1];
	app->philos[0].r_fork = &app->forks[0];
	i = -1;
	while (++i < app->philo_count)
	{
		init_philo(app, i);
		//printf("philo %i initiliazed, their id: %i\n", i, app->philos[i].philo_id);
		if (i != 0)
			app->philos[i].l_fork = &app->forks[i - 1];
		if (i != 0)
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
