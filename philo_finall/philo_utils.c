#include "./philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str, unsigned long *tab_num)
{
	int				i;
	unsigned long	num;

	if (!str)
		return (-1);
	i = 0;
	num = 0;
	while (str[i] != '\0' && (str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			return (-1);
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		num = (num * 10) + (str[i++] - 48);
		if (num > INT_MAX)
			return (-1);
	}
	if (str[i] != '\0' && !(str[i] == 32 || (str[i] <= 13 && str[i] >= 9)))
		return (-1);
	if (tab_num)
		*tab_num = num;
	return (0);
}

uint64_t	get_curr(uint64_t time_init)
{
	struct timeval	tv;
	uint64_t		curr;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	curr = ((uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
	curr = curr - time_init;
	return (curr);
}

void	ph_sleep(uint64_t duration)
{
	uint64_t	start;

	start = get_curr(0);
	while ((get_curr(0) - start) < duration)
		usleep(100);
}

int		ph_print(t_philo *phi, char *act)
{	
	uint64_t		curr;
	
	if (phi->ate == phi->table->must_eat)
		return (-1);
	curr = get_curr(phi->table->time_init);
	if (!curr)
		return (-1);
	sem_wait(phi->table->sem_print);
	printf("%lu\t%i %s\n", curr, phi->id, act);
	if (!ft_strcmp(act, MSG_DIED))
		return (1);
	sem_post(phi->table->sem_print);
	return (0);
}
