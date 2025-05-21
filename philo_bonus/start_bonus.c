/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:34:19 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/15 17:56:56 by beldemir         ###   ########.fr       */
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
			exit (1);
		}
		usleep(100);
	}
}

static int	init_semaphores(t_info *info)
{
	sem_unlink("/s_forks");
	sem_unlink("/s_write");
	sem_unlink("/s_death");
	info->s_forks = sem_open("/s_forks", O_CREAT | O_EXCL, 0644, \
	info->philo_count);
	info->s_write = sem_open("/s_write", O_CREAT | O_EXCL, 0644, 1);
	info->s_death = sem_open("/s_death", O_CREAT | O_EXCL, 0644, 0);
	if (info->must_eat > 0)
	{
		sem_unlink("/ate");
		info->s_ate = sem_open("/ate", O_CREAT | O_EXCL, 0644, 0);
		if (info->s_ate == SEM_FAILED)
		{
			cleanup(info);
			return (-1);
		}
	}
	if (info->s_forks == SEM_FAILED || info->s_write == SEM_FAILED || \
	info->s_death == SEM_FAILED)
	{
		cleanup(info);
		return (-1);
	}
	return (0);
}

static void	init_philo(t_info *info, pid_t *pids)
{
	int	i;

	i = -1;
	while (++i < info->philo_count)
	{
		info->philo.info = info;
		info->time_init = get_current();
		pids[i] = fork();
		if (pids[i] == 0)
		{
			info->philo.id = i + 1;
			info->philo.eat_count = 0;
			info->philo.last_meal = 0;
			pthread_create(&info->philo.self_monitor, \
			NULL, monitor, (void *)&info->philo);
			(pthread_detach(info->philo.self_monitor), routine(&info->philo));
			return ;
		}
		else if (pids[i] < 0)
		{
			while (--i >= 0)
				kill(pids[i], SIGKILL);
			break ;
		}
	}
}

static void	should_quit(t_info *info, pid_t *pids)
{
	int	i;
	int	done_eat;

	done_eat = 0;
	while (1)
	{	
		if (sem_wait(info->s_death) == 0)
			break ;
		if (info->must_eat > 0 && done_eat < info->philo_count && \
		info->s_ate)
		{
			if (sem_wait(info->s_ate) == 0)
				done_eat++;
			if (done_eat == info->philo_count)
				break ;
		}
	}
	i = -1;
	while (++i < info->philo_count)
		kill(pids[i], SIGKILL);
}

int	start(int ac, char **av)
{
	t_info	info;
	pid_t	*pids;
	int		i;

	init_start(ac, av, &info);
	if (init_semaphores(&info) != 0)
		return (-1);
	pids = (pid_t *)malloc(sizeof(pid_t) * info.philo_count);
	if (!pids)
		(cleanup(&info), exit(1));
	sem_init(&info.s_done, 0, 0);
	init_philo(&info, pids);
	i = -1;
	while (++i < info.philo_count)
		sem_wait(&info.s_done);
	(should_quit(&info, pids), free(pids), cleanup(&info));
	return (0);
}
