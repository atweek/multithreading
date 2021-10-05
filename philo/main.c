#include "philo.h"

int find_errors(int argc)
{
    if (argc > 6 || argc < 5)
		return 0;
	return 1;//ADD
}

int add_philo()
{

}

int init_philo(t_all *all,int argc, char **argv)
{
	int i;
	int len;
	len = ft_atoi(argv[1]);
	all->table->forks = malloc(sizeof(pthread_mutex_t) * len);
	if (all->table->forks == NULL)
		return 0;
	i = 0;
	while (i < len)
		pthread_mutex_init(&all->table->forks[i++],NULL);
	all->philo = malloc(sizeof(t_philo) * len);
	if (all->philo == NULL)
		return 0;
	while (i < len)
	{
		all->philo[i].id = i + 1;
		all->philo[i].sleep = ft_atoi(argv[3]);
		all->philo[i].time_eat = ft_atoi(argv[4]);
		all->philo[i].time_dead = ft_atoi(argv[2]);//point

	
	i = 0;
	while (i < len)
	{
		if (i == 0)
		{
			all->philo[i].left_fork = all->table->forks[len -1];
			all->philo[i].right_fork = all->table->forks[i];
		}
		else
		{
			all->philo[i].left_fork = all->table->forks[i-1];
			all->philo[i].right_fork = all->table->forks[i];
		}
		i++;
	}
	
	return 1;
}

int live()
{
	//каждому 
}

int start(t_all)
{
	//start live (potoki sozd)po kolvo philo
	//проверка живы ли филы gettimeofday
}

int main(int argc, char **argv)
{
	t_all all;

    if (find_errors(argc) != 1)
		return 0;//error
	if (init_philo(&all,argc,argv) != 1)
		return 0;
	if(live() != 1)
		return 0;
	
}