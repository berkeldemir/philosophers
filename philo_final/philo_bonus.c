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
	ütable->s_forks = sem_open("/s_forks", O_CREAT, 0644, num_philos);
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
	if (!table->pids)
		return (-1);
	i = -1;
	while (++i < )
}

int main(int ac, char **av)
{
	t_table table;

	if (arg_check(ac, av) != 0)
		return (1);
	if (table_init(ac, av, &table) != 0)
		return (2);
	if (philos_init(&table) != 0)
		return (3);

	return (0);
}
