/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:56:37 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/26 09:46:34 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	arg_check(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i], NULL) != 0)
			return (-1);
		i++;
	}
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
	//free();
	return (0);
}
