/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:08:31 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/15 18:20:31 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int arg_check_and_assign(int ac, char **av, t_info *info)
{
    int i;

    i = 0;
    while (++i < ac)
    if (ft_atoi(av[i], NULL) != 0)
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    t_info  info;

    if (arg_check_and_assign(ac, av, &info))
        return (1);
}