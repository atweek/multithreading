#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
    unsigned int	id;
	unsigned int	time_start;
	unsigned int	time_dead;
	unsigned int	time_eat;
	unsigned int	count_eat;
	unsigned int	time_sleep;
	unsigned int	last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				die;
} t_philo;

typedef struct s_table {
    pthread_mutex_t *forks;
} t_table;

typedef struct s_all
{
	t_philo *philo;
	t_table *table;
	int		ph_count;
	// unsigned int	start;
	struct timeval	*start;
	struct timezone	*start_tz;
	pthread_t undertaker;
} t_all;


/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
4 400 200 100

20 
1 8 1
8   8
1 8 1


./pfilo kolvo time_to_dead eat sleep 
*/

int		ft_atoi(const char *str);
long	get_time(struct timeval *time);
void	ft_usleep(unsigned int milliseconds);
void	*live(t_all *all);

#endif