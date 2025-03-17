/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:38:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/17 20:47:32 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	//printf("\nphilo_id:%i\n", *(int *)arg);
	return (NULL);
}

uint64_t	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL));
}

void	elapsed_time(uint64_t init_time)
{
	printf("%s%05lu: %s", PURPLE, (get_time() - init_time), DEFAULT);
}

int	check_args(int ac, char **av, t_app *app)
{
	if (ac == 5 || ac == 6)
	{
		while (--ac > 0)
			if (!ft_isnum(av[ac]))
				return (-1);
		return (0);
	}
	else
		return (-1);
}

int main(int ac, char **av)
{
	t_app		app;

	if (check_args(ac, av, &app) == -1)
		return (1);
	init(&app);
	app.init_time = get_time();
	elapsed_time(app.init_time);
	sleeping(1);
	usleep(2000000); // 2 saniye bekle
	sleep(2);
	elapsed_time(app.init_time);
	died(4);
	return 0;
}
