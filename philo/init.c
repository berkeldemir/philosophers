/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:46:40 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/17 20:46:26 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int    init(t_app *app)
{
	int			i;

	app->count = 5;
	app->philo = (pthread_t *)malloc(sizeof(pthread_t) * app->philo_count);
	if (!app->philo)
		return (-1);
	app->philo_id = (int *)malloc(sizeof(int) * app->count);
	if (!app->philo_id)
		return (-1);
	i = -1;
	while (++i < app->count)
		app->philo_id[i] = i + 1;
	i = -1;
	while (++i < app->count)
	{
		if (pthread_create(&app->philo[i], NULL, \
		&routine, &app->philo_id[i]) != 0)
			return (-1);
		//thinking(app->philo_id[i]);
	}
	i = -1;
	while (++i < app->count)
		pthread_join(app->philo[i], NULL);
	return (0);
}
