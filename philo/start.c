/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/18 21:16:27 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	*routine(void *arg)
{
	t_app		*app;

	app = (t_app *)arg;
	return (NULL);
}

int	start(t_app *app)
{
	int	i;

	app->philos = (t_philo *)malloc(sizeof(t_philo) * app->philo_count);
	if (!app->philos)
		return (1);
	i = -1;
	while (++i < app->philo_count)
	{
		app->philos[i].philo_id = i + 1;
		app->philos[i].meals_had = 0;
		app->philos[i].full = FALSE;
		app->philos[i].last_eaten = 0;
		app->philos[i].l_fork = NULL;
		app->philos[i].r_fork = NULL;
		pthread_create(&app->philos[i].thread, NULL, routine, (void *)&app);
	}
	i = -1;
	while (++i < app->philo_count)
		pthread_join(app->philos[i].thread, NULL);
	return (0);
}
