#include "./philo_bonus.h"

void	exit_noleak(t_table *table)
{
	(void)table;
	if (table->pids)
		free(table->pids);
	if (table->sem_forks)
		sem_close(table->sem_forks);
	if (table->sem_print)
		sem_close(table->sem_print);
	return ;
}

void	routine(t_philo *phi)
{
	if (phi->id % 2 == 1)
		usleep(500);
	int i = 1;
	while (i)
	{
		i = 0;
		sem_wait(phi->table->sem_print);
		printf("%i in action.\n", phi->id);
		sem_post(phi->table->sem_print);
		usleep(200);
	}
	exit_noleak(phi->table);
}

void	*thread_routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	(void)phi;
	sem_wait(phi->table->sem_print);
	printf("%i thread routine action.\n", phi->id);
	sem_post(phi->table->sem_print);
	usleep(200);
	exit_noleak(phi->table);
	return (NULL);
}
