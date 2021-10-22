#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	pthread_mutex_t	*forks;
}	t_table;

typedef struct s_philo
{
	struct timeval	*start;
	pthread_t		thread;
	unsigned int	id;
	unsigned int	time_start;
	unsigned int	time_dead;
	unsigned int	time_eat;
	int				count_eat;
	unsigned int	time_sleep;
	unsigned int	last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				die;
}	t_philo;
typedef struct s_all
{
	t_philo			*philo;
	t_table			*table;
	int				ph_count;
	struct timeval	*start;
	int				check_eat;
	struct timezone	*start_tz;
}	t_all;

int		ft_atoi(const char *str);
long	get_time(struct timeval *time);
void	ft_usleep(unsigned int milliseconds);
void	*live(t_philo *philo);
void	birth(t_all *all);
int		ft_isdigit(int c);

#endif