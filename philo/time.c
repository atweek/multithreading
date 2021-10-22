#include "philo.h"

int	free_exit(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->ph_count)
		pthread_detach(all->philo[i++].thread);
	free(all->table->forks);
	free(all->philo);
	free(all->start_tz);
	free(all->start);
	free(all->table);
	return (0);
}

void	ft_usleep(unsigned int milliseconds)
{
	long	cur_time;
	long	start;

	start = get_time(NULL);
	cur_time = get_time(NULL);
	while (cur_time - start < milliseconds)
	{
		cur_time = get_time(NULL);
	}
}

long	get_time(struct timeval *time)
{
	struct timeval	cur_time;
	struct timezone	tz;

	gettimeofday(&cur_time, &tz);
	if (time == NULL)
		return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
	cur_time.tv_sec = cur_time.tv_sec - time->tv_sec;
	cur_time.tv_usec = cur_time.tv_usec - time->tv_usec;
	if (cur_time.tv_usec < 0)
	{
		cur_time.tv_sec--;
		cur_time.tv_usec += 1000000;
	}
	return (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000);
}
