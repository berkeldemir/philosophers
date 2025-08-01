/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:02:47 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/15 16:28:42 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_start(int ac, char **av, t_info *info)
{
	ft_atoi(av[1], (unsigned long *)&info->philo_count);
	ft_atoi(av[2], (unsigned long *)&info->time_to_die);
	ft_atoi(av[3], (unsigned long *)&info->time_to_eat);
	ft_atoi(av[4], (unsigned long *)&info->time_to_sleep);
	info->must_eat = -1;
	if (ac == 6)
		ft_atoi(av[5], (unsigned long *)&info->must_eat);
	info->philos = NULL;
	info->forks = NULL;
	info->quit = FALSE;
	memset(&info->write_lock, 0, sizeof(pthread_mutex_t));
	memset(&info->quit_lock, 0, sizeof(pthread_mutex_t));
}

void	ph_sleep(uint64_t duration)
{
	uint64_t	start;

	start = get_current();
	while ((get_current() - start) < duration)
		usleep(100);
}

int	ft_atoi(const char *str, unsigned long *tab_num)
{
	int				i;
	unsigned long	num;

	if (!str)
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
	if (str[i] != '\0' && !(str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		return (-1);
	if (tab_num)
		*tab_num = num;
	return (0);
}
