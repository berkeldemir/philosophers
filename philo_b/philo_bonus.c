#include "./philo_bonus.h"

static void	routine(t_philo *phi)
{
	sem_wait(phi->data->start);
	phi->last_meal = elapsed_time(phi->data);
	if (phi->id % 2 == 1)
		ph_sleep(phi->data->time_to_eat / 2);
	//write(1, "XX", 2);
	while (1)
	{
		sem_wait(phi->data->forks);
		action(phi, MSG_TAKENFORK);
		sem_wait(phi->data->forks);
		action(phi, MSG_TAKENFORK);
		action(phi, MSG_EATING);
		phi->last_meal = elapsed_time(phi->data);
		phi->eat_count++;
		ph_sleep(phi->data->time_to_eat);
		(sem_post(phi->data->forks), sem_post(phi->data->forks));
		if (phi->data->must_eat != -1 && phi->eat_count >= phi->data->must_eat)
			break ;
		action(phi, MSG_SLEEPING);
		ph_sleep(phi->data->time_to_sleep);
		action(phi, MSG_THINKING);
	}
}

static int	ph_init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->time_init = get_current();
	while (++i < data->philo_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			data->philo[i].data = data;
			data->philo[i].eat_count = 0;
			data->philo[i].last_meal = 0;
			data->philo[i].id = i + 1;
			pthread_create(&data->philo[i].monitor, NULL, monitor, \
			(void *)&data->philo[i]);
			pthread_detach(data->philo[i].monitor);
			routine(&data->philo[i]);
			return (1);
		}
		else if (data->pids[i] < 0)
		{
			while (--i >= 0)
				kill(data->pids[i], SIGKILL);
			return (cleanup(data), 1);
		}
	}
	return (0);
}

static int	ph_init_semaphores(t_data *data)
{
	sem_unlink("/start");
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/quit");
	data->start = sem_open("/start", O_CREAT | O_EXCL, 0644, 0);
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, \
	data->philo_count);
	data->write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1);
	data->quit = sem_open("/quit", O_CREAT | O_EXCL, 0644, 1);
	if (data->start == SEM_FAILED || data->forks == SEM_FAILED || \
		data->write == SEM_FAILED || data->quit == SEM_FAILED)
		return (cleanup(data), 1);
	return (0);
}

static int ph_init(int ac, char **av, t_data *data)
{	
	int	i;

	if (ac != 5 && ac != 6)
		return (1);
	i = 0;
	while (++i < ac)
		if (ft_atoi(av[i], NULL) != 0)
			return (-1);
	ft_atoi(av[1], (unsigned long *)&data->philo_count);
	ft_atoi(av[2], (unsigned long *)&data->time_to_die);
	ft_atoi(av[3], (unsigned long *)&data->time_to_eat);
	ft_atoi(av[4], (unsigned long *)&data->time_to_sleep);
	data->must_eat = -1;
	if (ac == 6)
		ft_atoi(av[5], (unsigned long *)&data->must_eat);
	if (data->philo_count > MAX_PHILO || data->philo_count < 1)
		return (-1);
	data->start = NULL;
	data->forks = NULL;
	data->write = NULL;
	data->quit = NULL;
	data->exit = FALSE;
	return (0);
}

int	main(int ac, char **av)
{
	t_data  data;

	if (ph_init(ac, av, &data) != 0)
		return (1);
	if (ph_init_semaphores(&data) != 0)
		return (2);
	data.pids = (pid_t *)malloc(sizeof(pid_t) * data.philo_count);
	if (!data.pids)
		return (cleanup(&data), 1);
	data.philo = (t_philo *)malloc(sizeof(t_philo) * data.philo_count);
	if (!data.philo)
		return (cleanup(&data), 2);
	if (ph_init_philos(&data) != 0)
		return (cleanup(&data), 3);
	ph_wait_to_end(&data);
	cleanup(&data);
	exit(0);
}
