
#include "philo.h"

void eating(t_philo *philo,t_all *all)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->left_fork)
		printf("%ld %d has taken a fork\n", 
			get_time(all->start),philo->id);
    pthread_mutex_lock(philo->right_fork);
	if (philo->right_fork)
		printf("%ld %d has taken a fork\n", 
			get_time(all->start),philo->id);
	if (philo->left_fork && philo->right_fork)
	{
		printf("%ld %d is eating\n",get_time(all->start),philo->id);
		philo->last_eat = get_time(NULL);
	}
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->left_fork);

}

void sleeping(t_philo *philo,t_all *all)
{
	printf("%ld %d is sleeping\n", 
			get_time(all->start),philo->id);
	ft_usleep(philo->time_sleep);
}

void thinking(t_philo *philo,t_all *all)
{
	printf("%ld %d is thinking\n", get_time(all->start),philo->id);
}

void *live(t_all *all)
{
	if (all->philo->id % 2 == 0)
		usleep(20);
	while (all->philo->die == 0)
	{
		if (all->philo->time_dead - all->philo->last_eat <= 0)
		{
			all->philo->die = 1;
			break ;
		}
		eating(all->philo,all);
		sleeping(all->philo,all);
		thinking(all->philo,all); 
	}
	return (NULL);
}