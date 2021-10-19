#include "philo.h"

int	ft_isspace_bonus(int ch)
{
	if (((ch >= 9) && (ch <= 13)) || (ch == 32))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if ((c > 47) && (c < 58))
		return (1);
	return (0);
}

static int	check_minus_max(unsigned long long num, int minus)
{
	if (num > 9223372036854775807)
	{
		if (minus)
			return (0);
		else
			return (-1);
	}
	if (minus == 1)
		num *= -1;
	if (minus > 1)
		num = 0;
	return (num);
}

static int	move(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isspace_bonus((int)str[i]))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					minus;
	unsigned long long	num;

	minus = 0;
	num = 0;
	i = move((char *)str);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			minus++;
	while (str[i] != '\0')
	{
		if (ft_isdigit((int)str[i]))
			num = (num * 10) + (str[i++] - 48);
		else
			break ;
	}
	return (check_minus_max(num, minus));
}
