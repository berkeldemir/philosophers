#include "./philo_bonus.h"

static int	arg_control(int ac, char **av)
{
	int	i;

	if (!(ac == 5 || ac == 6))
		return (1);
	i = 0;
	while (++i < ac)
		if (ft_atoi(av[i], NULL) != 0)
			return (1);
	return (0);
}

static int	init_table(int ac, char **av, t_table *table)
{
	ft_atoi(av[1], (unsigned long *)&table->philo_count);
	ft_atoi(av[2], &table->time2die);
	ft_atoi(av[3], &table->time2eat);
	ft_atoi(av[4], &table->time2sleep);
	if (ac == 6)
		ft_atoi(av[5], (unsigned long *)&table->must_eat);
	else
		table->must_eat = -1;
	sem_unlink("/forks");
	sem_unlink("/print");
	table->sem_forks = sem_open("/forks", O_CREAT, 0666, table->philo_count);
	table->sem_print = sem_open("/print", O_CREAT, 0666, 1);
	if (table->sem_forks == SEM_FAILED || table->sem_print == SEM_FAILED)
		return (exit_noleak(table), 1);
	return (0);
}

static int	revive_philo(t_table *table, int i)
{
	t_philo	*phi;

	phi = (t_philo *)malloc(sizeof(t_philo));
	if (!phi)
		return (1);
	printf("philo %d revived\n", i + 1);
	phi->id = i + 1;
	phi->ate = 0;
	phi->last_meal = 0;
	phi->table = table;
	pthread_create(&phi->thread, NULL, thread_routine, phi);
	routine(phi);
	pthread_detach(phi->thread);
	exit_noleak(table);
	return (0);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	table->pids = (pid_t *)malloc(sizeof(pid_t) * table->philo_count);
	if (!table->pids)
		return (1);
	while (++i < table->philo_count)
	{
		table->pids[i] = fork();
		if (table->pids[i] == 0)
		{
			if (revive_philo(table, i))
				return (1);
			return (0);
		}
		else if (table->pids[i] == -1)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (arg_control(ac, av))
		return (1);
	if (init_table(ac, av, &table))
		return (2);
	if (init_philos(&table))
		return (3);
}
