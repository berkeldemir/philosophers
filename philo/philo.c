/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:38:14 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/11 19:38:51 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	printf("\nphilo_id:%i\n", *(int *)arg);
	return (NULL);
}

static long	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	print_time(long init_time)
{
	printf("%ld", get_time() - init_time);
}

int	main(int ac, char **av)
{
	t_app		app;
	long init_time = get_time();
	if (init(&app) == -1)
		return (1);
	print_time(init_time);
	usleep(3000);
	printf("\n");
	print_time(init_time);
	//printf("sec : %ld\n", app.tv.tv_sec);
	//printf("msec: %ld\n", app.tv.tv_usec);
}
