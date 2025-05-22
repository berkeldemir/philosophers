/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:34:19 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/22 15:18:43 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static void	*monitor(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (1)
	{
		if (elapsed_time(phi->info) - phi->last_meal > phi->info->time_to_die)
		{
			action(phi, MSG_DIED);
			sem_post(phi->info->s_death);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

static int	init_semaphores(t_info *info)
{
	sem_unlink("/s_forks");
	sem_unlink("/s_write");
	sem_unlink("/s_death");
	sem_unlink("/s_done");
	info->s_ate = SEM_FAILED;
	info->s_forks = sem_open("/s_forks", O_CREAT | O_EXCL, 0644, \
	info->philo_count);
	info->s_write = sem_open("/s_write", O_CREAT | O_EXCL, 0644, 1);
	info->s_death = sem_open("/s_death", O_CREAT | O_EXCL, 0644, 0);
	info->s_done = sem_open("/s_done", O_CREAT | O_EXCL, 0644, 0);
	if (info->must_eat > 0)
	{
		sem_unlink("/s_ate");
		info->s_ate = sem_open("/s_ate", O_CREAT | O_EXCL, 0644, 0);
		if (info->s_ate == SEM_FAILED)
			return (cleanup(info), -1);
	}
	if (info->s_forks == SEM_FAILED || info->s_write == SEM_FAILED || \
		info->s_death == SEM_FAILED || info->s_done == SEM_FAILED)
			return (cleanup(info), -1);
	return (0);
}

static int	init_philo(t_info *info)
{
	int	i;

	info->philo.info = info;
	info->time_init = get_current();
	info->philo.eat_count = 0;
	info->philo.last_meal = 0;
	i = -1;
	while (++i < info->philo_count)
	{
		info->pids[i] = fork();
		if (info->pids[i] == 0)
		{
			info->philo.id = i + 1;
			pthread_create(&info->philo.self_monitor, \
			NULL, monitor, (void *)&info->philo);
			routine(&info->philo);
			return (pthread_join(info->philo.self_monitor, NULL), 1);
		}
		else if (info->pids[i] < 0)
		{
			while (--i >= 0)
				kill(info->pids[i], SIGKILL);
			return (0);
		}
	}
	return (1);
}

static void	*watcher(void *arg)
{
	int		done_eat;
	t_info	*info;

	done_eat = 0;
	info = (t_info *)arg;
	while (done_eat < info->philo_count)
		if (sem_wait(info->s_ate) == 0)
			done_eat++;
	sem_post(info->s_death);
	return (NULL);
}

int	start(int ac, char **av)
{
	t_info	info;
	int		i;

	init_start(ac, av, &info);
	if (init_semaphores(&info) != 0)
		return (-1);
	info.pids = (pid_t *)malloc(sizeof(pid_t) * info.philo_count);
	if (!info.pids)
		(cleanup(&info), exit(1));
	if (init_philo(&info) == 0)
		(cleanup(&info), exit(1));
	i = -1;
	/*while (++i < info.philo_count)
		sem_wait(info.s_done);*/
	if (info.must_eat > 0)
		(pthread_create(&info.watcher, NULL, watcher, &info), \
		pthread_join(info.watcher, NULL));
	sem_wait(info.s_death);
	i = -1;
	while (++i < info.philo_count)
		kill(info.pids[i], SIGKILL);
	(cleanup(&info), exit(0));
	return (0);
}
