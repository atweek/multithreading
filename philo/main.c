#include "philo.h"

int find_errors(int argc)
{
    if (argc > 6 || argc < 5)
		return 0;
	return 1;//ADD
}

int init_philo(t_all *all,char **argv)
{
	int i;
	int len;

	// all->start = get_time(NULL);
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
		all->philo[i].all = all;
		all->philo[i].id = i + 1;
		// printf("\nhello filo %d\n",all->philo[i].id);
		all->philo[i].time_dead = ft_atoi(argv[1]);
		all->philo[i].time_eat = ft_atoi(argv[2]);
		all->philo[i].time_sleep = ft_atoi(argv[3]);
		all->philo[i].count_eat = ft_atoi(argv[4]);
		all->philo[i].die = 0;
		i ++;
	}
	i = 0;
	while (i < len)
	{
		if (i == 0)
		{
			all->philo[i].left_fork = &all->table->forks[len -1];
			all->philo[i].right_fork = &all->table->forks[i];
		}
		else
		{
			all->philo[i].left_fork = &all->table->forks[i-1];
			all->philo[i].right_fork = &all->table->forks[i];
		}
		i++;
	}
	return 1;
}

// int live(t_all *all)
// {
// }

// int undertaker()
// {
// }

void birth(t_all *all)
{
	int i;

	all->start = (struct timeval *)malloc(sizeof(struct timeval));
	all->start_tz = (struct timezone *)malloc(sizeof(struct timezone));
	// if (!all->start || !sll->start_tz)
	// 	//erro
	gettimeofday(all->start, all->start_tz);
	i = 0;
	while (i < all->ph_count)
	{
		printf("run %d\n",all->philo[i].id);
		pthread_create(&all->philo[i].thread,NULL,(void *)live,(void *) all->philo[i]);
		i++;
	}
	i = 0;
	while (i < all->ph_count)
		pthread_detach(all->philo[i++].thread);
	ft_usleep(20);
	// pthread_create(&all->undertaker,NULL,undertaker,(void *) &all);
	// цикл для прохода по филам и смотрю есть ли у них время и жизнь
}

int main(int argc, char **argv)
{
	t_all all;
	all.table = malloc(sizeof(t_table));
    if (find_errors(argc) != 1)
		return 0;//error
	if (init_philo(&all,argv) != 1)
		return 0;
	birth(&all);
	live(&all);
	// 	return 0;
	
}