#ifndef PHILO_BONUS
# define PHILO_BONUS

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

# define MAX_PHILO 200

# define MSG_TAKENFORK "has taken a fork"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_EATING "is eating"
# define MSG_DIED "died"

typedef enum	e_bool	t_bool;
typedef struct	s_philo	t_philo;
typedef struct	s_data	t_data;

typedef enum e_bool
{
    FALSE = 0,
    TRUE = 1
}	t_bool;

typedef struct	s_philo
{
	int				id;
	int				eat_count;
	uint64_t		last_meal;
	pthread_t		monitor;
	struct s_data	*data;
}   t_philo;

typedef struct	s_data
{
	pid_t		*pids;
	sem_t		*start;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*quit;
	t_bool		exit;
	t_philo 	philo;
	int			philo_count;
	uint64_t	time_init;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			must_eat;
}	t_data;

// action.c
void		ph_sleep(uint64_t duration);
uint64_t	get_current(void);
uint64_t	elapsed_time(t_data	*data);
int			action(t_philo *phi, char *action);

// threads.c
void	*monitor(void *arg);
void	ph_wait_to_end(t_data *data);

// utils.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str, unsigned long *tab_num);
void	cleanup(t_data *data);

#endif

