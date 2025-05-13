/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beldemir <beldemir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:34:19 by beldemir          #+#    #+#             */
/*   Updated: 2025/05/13 22:17:36 by beldemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static void	*monitor(void *arg)
{
	t_phi	*phi;

	phi = (t_phi *)arg;
	while (1)
	{
		if (get_current() - phi->last_meal > phi->info->time_to_die)
		{
			sem_wait(phi->info->s_write);
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
	info->s_death = sem_open("/s_death", O_CREAT | O_EXCL, 0644, 1);
	if (info->must_eat > 0)
	{
		sem_unlink("/done_eating");
		info->s_done_eating = sem_open("/done_eating", O_CREAT | \
		O_EXCL, 0644, 0);
	}
	if (info->s_forks == SEM_FAILED || info->s_write == SEM_FAILED || \
	info->s_death == SEM_FAILED)
		cleanup(info);
	if (info->must_eat > 0)
		if (info->s_done_eating == SEM_FAILED)
			cleanup(info);
	return (0);
}

static void	init_philo(t_info *info, int i)
{
	if (i >= 0)
		info->philos[i].id = i + 1;
	info->philos[i].eat_count = 0;
	info->philos[i].last_meal = 0;
	pthread_create(&info->philos[i].self_monitor, \
	NULL, monitor, (void *)&info->philos[i]);
	pthread_detach(info->philos[i].self_monitor);
	routine(&info->philos[i]);
}

static void	should_quit(t_info *info, pid_t *pids)
{
	int	i;
	int	done_eat;
	int	death;

	done_eat = 0;
	death = 0;
	while (1)
	{
		if (sem_wait(info->s_death) == 0)
		{
			death = 1;
			break ;
		}
		if (info->must_eat > 0 && done_eat < info->philo_count && \
		info->s_done_eating)
		{
			if (sem_wait(info->s_done_eating) == 0)
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
	init_semaphores(&info);
	pids = (pid_t *)malloc(sizeof(pid_t) * info.philo_count);
	if (!pids)
		return (-1);
	i = -1;
	while (++i < info.philo_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			(init_philo(&info, i), exit(0));
	}
	should_quit(&info, pids);
	free(pids);
	return (0);
}
