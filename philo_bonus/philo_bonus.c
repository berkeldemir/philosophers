/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:32:12 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/05 21:32:43 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static int	arg_check(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (ft_atoi(av[i], NULL) != 0)
			return (-1);
	ft_atoi(av[1], (unsigned long *)&i);
	if (i > MAX_PHILO)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (arg_check(ac, av) != 0)
		return (2);
	if (start(ac, av) != 0)
		return (3);
	return (0);
}
