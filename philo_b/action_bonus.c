#include "./philo_bonus.h"

void	ph_sleep(uint64_t duration)
{
	uint64_t	start;

	start = get_current();
	while ((get_current() - start) < duration)
		usleep(100);
}

uint64_t	get_current(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return ((uint64_t)(-1));
	return ((uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
}

uint64_t	elapsed_time(t_data	*data)
{
	return (get_current() - data->time_init);
}

int	action(t_philo *phi, char *action)
{
	sem_wait(phi->data->write);
	printf("%lu\t%i %s\n", elapsed_time(phi->data), phi->id, action);
	if (ft_strcmp(action, MSG_DIED) != 0)
		sem_post(phi->data->write);
	else
	{
		sem_wait(phi->data->quit);
		phi->data->exit = TRUE;
		sem_post(phi->data->quit);
	}
	return (0);
}

