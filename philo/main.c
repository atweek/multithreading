#include "philo.h"

int	find_errors(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	if (argc > 6 || argc < 5)
		return (0);
	i = 1;
	while (i < argc)
	{
		while (argv[i][j])
			if (ft_isdigit(argv[i][j++]) == 0)
				return (0);
		i++;
		j = 0;
	}
	return (1);
}

void	add_info(t_all *all, int len, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_init(&all->table->forks[i], NULL);
		all->philo[i].id = i + 1;
		all->philo[i].time_dead = ft_atoi(argv[2]);
		all->philo[i].time_eat = ft_atoi(argv[3]);
		all->philo[i].time_sleep = ft_atoi(argv[4]);
		if (argc > 5)
		{
			all->check_eat = 1;
			all->philo[i].count_eat = ft_atoi(argv[5]);
		}
		else
			all->check_eat = 0;
		all->philo[i].die = 0;
		i++;
	}
}

void	init_philo(t_all *all, char **argv, int argc)
{
	int	len;
	int	i;

	i = -1;
	len = ft_atoi(argv[1]);
	all->ph_count = len;
	all->table = malloc(sizeof(t_table));
	all->table->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * len);
	all->philo = malloc(sizeof(t_philo) * len);
	add_info(all, len, argv, argc);
	while (++i < len)
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
	}
}

int	count_eat(t_all *all)
{
	int	i;

	i = 0;
	if (all->check_eat == 1)
	{
		while (i < all->ph_count)
		{
			if (all->philo[i].count_eat > 0)
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;
	int		i;

	if (find_errors(argc, argv) != 1)
		return (0);
	init_philo(&all, argv, argc);
	birth(&all);
	while (1)
	{
		i = -1;
		ft_usleep(10);
		while (++i < all.ph_count)
		{
			if (count_eat(&all) == 0)
				return (free_exit(&all));
			if (all.philo[i].time_dead < (get_time(all.philo[i].start)
					- all.philo[i].last_eat))
			{
				all.philo[i].die = 1;
				printf("%ld %d died\n",
					get_time(all.philo[i].start), all.philo[i].id);
				return (free_exit(&all));
			}
		}
	}
}
