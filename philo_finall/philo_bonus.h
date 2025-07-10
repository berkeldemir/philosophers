#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>

# define MSG_TAKENFORK "has taken a fork"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_EATING "is eating"
# define MSG_DIED "died"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				ate;
	uint64_t		last_meal;
	pthread_t		thread;
	t_table			*table;
}   t_philo;

typedef struct s_table
{
	pid_t		*pids;
	int			philo_count;
	uint64_t	time2die;
	uint64_t	time2eat;
	uint64_t	time2sleep;
	uint64_t	time_init;
	int			must_eat;
	sem_t		*sem_forks;
	sem_t		*sem_print;
}	s_table;

// UTILS
void		exit_noleak(t_table *table);
void		ph_sleep(uint64_t duration);
uint64_t	get_curr(uint64_t time_init);
int			ph_print(t_philo *phi, char *act);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str, unsigned long *tab_num);

// ROUTINE
void	routine(t_philo *phi);
void	*thread_routine(void *arg);

#endif