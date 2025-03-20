/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:38:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 19:02:53 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(int ac, char **av, t_app *app)
{
	app->philo_count = ft_atoi(av[1]);
	app->time_to_die = ft_atoi(av[2]);
	app->time_to_eat = ft_atoi(av[3]);
	app->time_to_slp = ft_atoi(av[4]);
	app->max_meal = -1;
	if (ac == 6)
		app->max_meal = ft_atoi(av[5]);
}

static int	check_args(int ac, char **av, t_app *app)
{
	int	i;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		while (++i < ac)
		{
			if (ft_isnum(av[i]))
				return (1);
		}
		init_args(ac, av, app);
		return (0);
	}
	else
		return (1);
}

int	main(int ac, char **av)
{
	t_app		app;
	int			i;

	if (check_args(ac, av, &app) != 0)
		return (1);
	app.start = get_time();
	if (start(&app) != 0)
		return (1);
	if (app.philos)
		free(app.philos);
	if (app.forks)
		free(app.forks);
	i = -1;
	while (++i < app.philo_count)
		pthread_mutex_destroy(&app.forks[i]);
	return (0);
}
