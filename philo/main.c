#include "philo.h"

int find_errors(int argc)
{
    if (argc > 6 || argc < 5)
		return 0;
	return 1;
}

int init_philo(t_all *all,char **argv,int argc)
{
	int i;
	int len;

	len = ft_atoi(argv[1]);
	all->ph_count = len;
	all->table->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * len);
	if (all->table->forks == NULL)
		return 0;
	i = 0;
	while (i < len)
		pthread_mutex_init(&all->table->forks[i++],NULL);
	all->philo = malloc(sizeof(t_philo) * len);
	if (all->philo == NULL)
		return 0;
	i = 0;
	while (i < len)
	{
		all->philo[i].id = i + 1;
		all->philo[i].time_dead = ft_atoi(argv[2]);
		all->philo[i].time_eat = ft_atoi(argv[3]);
		all->philo[i].time_sleep = ft_atoi(argv[4]);
		if (argc > 5)
		{
			all->philo[i].check_eat = 1;
			all->philo[i].count_eat = ft_atoi(argv[5]);
		}
		else
			all->philo[i].check_eat = 0;
		all->philo[i].die = 0;
		i ++;
	}
	i = 0;
	while (i < len)
	{
		if (i < len - 1)
		{
			all->philo[i].left_fork = &all->table->forks[i];
			all->philo[i].right_fork = &all->table->forks[i + 1];
		}
		else
		{
			all->philo[i].left_fork = &all->table->forks[i];
			all->philo[i].right_fork = &all->table->forks[0];
		}
		i++;
	}
	return 1;
}

void birth(t_all *all)
{
	int i;

	all->start = (struct timeval *)malloc(sizeof(struct timeval));
	all->start_tz = (struct timezone *)malloc(sizeof(struct timezone));
	gettimeofday(all->start, all->start_tz);
	i = 0;
	while (i < all->ph_count)
	{
		all->philo[i].start = all->start;
		pthread_create(&all->philo[i].thread,NULL,(void *)live,(void *) &all->philo[i]);
		i++;
	}
	i = 0;
	while (i < all->ph_count)
		pthread_detach(all->philo[i++].thread);
	ft_usleep(20);
}

int free_exit(t_all *all)
{
	free(all->table->forks);
	free(all->philo);
	free(all->start_tz);
	free(all->start);
	free(all->table);
	return 0;
}

int main(int argc, char **argv)
{
	t_all all;
	int i;

    if (find_errors(argc) != 1)
		return 0;
	all.table = malloc(sizeof(t_table));
	if (init_philo(&all,argv,argc) != 1)
		return 0;	
	birth(&all);
	while (1)
	{
		i = 0;
		while (i < all.ph_count)
		{
			if (all.philo[i].count_eat <= 0 && all.philo[i].check_eat == 1)
				return (free_exit(&all));
			if (all.philo[i].time_dead < (get_time(all.philo[i].start) - all.philo[i].last_eat))
			{
				all.philo[i].die = 1;
				printf("%ld %d died\n", get_time(all.philo[i].start),all.philo[i].id);
				return (free_exit(&all));
			}
			i++;
		}
	}
}