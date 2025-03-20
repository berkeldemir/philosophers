/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:48:27 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 15:27:07 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	taken_a_fork(uint64_t start, int philo_id)
{
	elapsed_time(start);
	printf("%s%i%s%s\n", YELLOW, philo_id, " has taken a fork", DEFAULT);
}

void	eating(uint64_t start, int philo_id)
{
	elapsed_time(start);
	printf("%s%i%s%s\n", ORANGE, philo_id, " is eating", DEFAULT);
}

void	sleeping(uint64_t start, int philo_id)
{
	elapsed_time(start);
	printf("%s%i%s%s\n", BLUE, philo_id, " is sleeping", DEFAULT);
}

void	thinking(uint64_t start, int philo_id)
{
	elapsed_time(start);
	printf("%s%i%s%s\n", GREEN, philo_id, " is thinking", DEFAULT);
}

void	died(uint64_t start, int philo_id)
{
	elapsed_time(start);
	printf("%s%i%s%s\n", RED, philo_id, " died ", DEFAULT);
}
