/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:02:47 by beldemir          #+#    #+#             */
/*   Updated: 2025/04/25 20:55:52 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return (-1);
	if (s1[i] || s2[i])
		return (-1);
	return (0);
}

int	ft_atoi(const char *str, int *tab_num)
{
	int		i;
	long	num;

	if (!*tab_num)
		return (-1);
	i = 0;
	num = 0;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			return (-1);
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		num = (num * 10) + (str[i++] - 48);
		if (num > INT_MAX)
			return (-1);
	}
	if (!(str[i] == '\0' || str[i] == ' '))
		return (-1);
	if (tab_num)
		*tab_num = num;
	return (0);
}
