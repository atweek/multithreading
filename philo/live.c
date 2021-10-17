
#include "philo.h"

void eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d has taken a fork\n", get_time(philo->start),philo->id);
    pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n",get_time(philo->start),philo->id);
	printf("%ld %d is eating\n",get_time(philo->start),philo->id);
	philo->last_eat = get_time(philo->start);
	philo->count_eat--;
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);

}

void sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", 
			get_time(philo->start),philo->id);
	ft_usleep(philo->time_sleep);
}

void thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time(philo->start),philo->id);
}

void *live(t_philo *philo)
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