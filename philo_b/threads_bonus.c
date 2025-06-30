#include "./philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*phi;
	t_bool	quit;
	
	phi = (t_philo *)arg;
	while (1)
	{
		sem_wait(phi->data->quit);
		quit = phi->data->exit;
		sem_post(phi->data->quit);
		if (quit == TRUE)
			return (NULL);
		if (elapsed_time(phi->data) - phi->last_meal > phi->data->time_to_die)
			break ;
		usleep(100);
	}
	action(phi, MSG_DIED);
	cleanup(phi->data);
	return (NULL);
}

void ph_wait_to_end(t_data *data)
{
	int i;
	int status;
	
	i = -1;
	while (++i < data->philo_count)
		sem_post(data->start);
	waitpid(-1, &status, 0);
	sem_wait(data->quit);
	data->exit = TRUE;
	sem_post(data->quit);
	i = -1;
	while (++i < data->philo_count)
		kill(data->pids[i], SIGKILL);
}