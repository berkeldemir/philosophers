/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:01:31 by beldemir          #+#    #+#             */
/*   Updated: 2025/07/04 15:01:32 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static int	arg_check(int ac, char **av)
{
	int	i;

	if (!(ac == 5 || ac == 6))
		return (-1);
	i = -1;
	while (++i < ac)
		if (ft_atoi(av[i], NULL) != 0)
			return (-1);
	return (0);
}

static int	table_init_semaphores(t_table *table)
{
	sem_unlink("/s_start");
	sem_unlink("/s_forks");
	sem_unlink("/s_print");
	sem_unlink("/s_read");
	table->s_start = sem_open("s_start", O_CREAT | O_EXCL, 0666, 0);
	table->s_forks = sem_open("/s_forks", O_CREAT | O_EXCL, 0666, \
	table->philo_count);
	table->s_print = sem_open("/s_print", O_CREAT | O_EXCL, 0666, 1);
	table->s_read = sem_open("/s_read", O_CREAT | O_EXCL, 0666, 1);
	if (table->s_start == SEM_FAILED || table->s_forks == SEM_FAILED\
	 || table->s_print == SEM_FAILED || table->s_read == SEM_FAILED)
		return (-1);
	return (0);
}

static int	table_init(int ac, char **av, t_table *table)
{
	ft_atoi(av[1], &table->philo_count);
	ft_atoi(av[2], &table->time_to_die);
	ft_atoi(av[3], &table->time_to_eat);
	ft_atoi(av[4], &table->time_to_sleep);
	if (ac == 6)
		ft_atoi(av[5], &table->must_eat);
	else
		table->must_eat = -1;
	table->s_start = NULL;
	table->s_forks = NULL;
	table->s_print = NULL;
	table->s_read = NULL;
	table->quit = FALSE;
	return (table_init_semaphores(&table));
}

static int	philos_init(t_table *table)
{
	int	i;

	table->pids = (pid_t *)malloc(sizeof(pid_t) * table->philo_count);
	table->phis = (t_phi *)malloc(sizeof(t_phi) * table->philo_count);
	if (!table->pids || !table->phis)
		return (-1);
	i = -1;
	while (++i < table->philo_count)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
		{
			table->phis[i].id = i + 1;
			table->phis[i].ate = 0;
			table->phis[i].last_meal = 0;
			table->phis[i].table = table;
			if (!pthread_create(&table->phis[i].self, NULL, ph_routine, \
			&table->phis[i]));
				return (-1);
			routine(table->phis[i]);
			return (i + 1);
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	t_table table;
	int		philos_init_ret_val;

	if (arg_check(ac, av) != 0)
		return (1);
	if (table_init(ac, av, &table) != 0)
		return (exit_noleak(&table), 2);
	philos_init_ret_val = philos_init(&table);
	if (philos_init_ret_val == -1)
		return (exit_noleak(&table), 3);
	if (philos_init_ret_val > 0)
		return (exit_noleak(&table), 0);
	dining(&table);
	return (0);
}
