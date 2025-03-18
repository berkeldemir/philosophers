/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:06:00 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/18 20:34:27 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL));
}

void	elapsed_time(uint64_t init_time)
{
	printf("%s%10lu: %s", PURPLE, (get_time() - init_time), DEFAULT);
}
