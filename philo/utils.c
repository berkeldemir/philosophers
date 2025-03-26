/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:02:47 by beldemir          #+#    #+#             */
/*   Updated: 2025/03/23 12:22:53 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_atoi(const char *str, int *tab_num)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		num = (num * 10) + (str[i++] - 48);
		if (num * (long)sign > INT_MAX || num * (long)sign < INT_MIN)
			return (-1);
	}
	if (!(str[i] == '\0' || str[i] == ' '))
		return (-1);
	if (tab_num)
		*tab_num = num * sign;
	return (0);
}
