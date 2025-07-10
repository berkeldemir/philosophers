#include "./philo_bonus.h"

void	exit_noleak(t_table *table)
{
	(void)table;
	exit(0);
}

void	routine(t_philo *phi)
{
	if (phi->id % 2 == 1)
		usleep(500);
	int i = 1;
	while (i)
	{
		i = 0;
		printf("%i in action.\n", phi->id);
		sleep(5);
	}
}

void	*thread_routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	(void)phi;
	return (NULL);
}
