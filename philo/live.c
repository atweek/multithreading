#include "philo.h"

void	birth(t_all *all)
{
	int	i;

	all->start = (struct timeval *)malloc(sizeof(struct timeval));
	all->start_tz = (struct timezone *)malloc(sizeof(struct timezone));
	gettimeofday(all->start, all->start_tz);
	i = 0;
	while (i < all->ph_count)
	{
		all->philo[i].start = all->start;
		pthread_create(&all->philo[i].thread, NULL,
			(void *)live, (void *) &all->philo[i]);
		i++;
	}
	i = 0;
	ft_usleep(20);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", get_time(philo->start), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", get_time(philo->start), philo->id);
	printf("%ld %d is eating\n", get_time(philo->start), philo->id);
	philo->last_eat = get_time(philo->start);
	philo->count_eat--;
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n",
		get_time(philo->start), philo->id);
	ft_usleep(philo->time_sleep);
}

void	thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time(philo->start), philo->id);
}

void	*live(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_usleep(20);
	while (philo->die == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
