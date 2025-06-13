#include "./philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*phi;
	t_bool	exit;
	
	phi = (t_philo *)arg;
	while (1)
	{
		sem_wait(phi->data->quit);
		exit = phi->data->exit;
		sem_post(phi->data->quit);
		if (exit == TRUE)
			return (NULL);
		if (elapsed_time(phi->data) - phi->last_meal > phi->data->time_to_die)
			break ;
		usleep(100);
	}
	action(phi, MSG_DIED);
	return (NULL);
}

void	*watcher(void *arg)
{
	int		done_eat;
	t_data	*data;

	done_eat = 0;
	data = (t_data *)arg;
	while (done_eat < data->philo_count)
		if (sem_wait(data->done) == 0)
			done_eat++;
	sem_wait(data->quit);
	data->exit = TRUE;
	sem_post(data->quit);
	return (NULL);
}

void	ph_wait_to_end(t_data *data)
{
	t_bool	exit;
	int		i;

	i = -1;
	while (++i < data->philo_count)
		sem_post(data->start);
	//write(1, "AB\n", 3);
	exit = FALSE;
	while (1)
	{
		sem_wait(data->quit);
		exit = data->exit;
		sem_post(data->quit);
		if (exit == TRUE)
			break ;
		usleep(1000);
	}
}
