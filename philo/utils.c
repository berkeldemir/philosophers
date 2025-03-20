/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:38:23 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/20 12:59:32 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '9' && str[i] <= '0')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		i;
	long	num;
	int		isneg;

	i = 0;
	num = 0;
	isneg = 1;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		i++;
	if (str[i] != '\0' && str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * isneg);
}
