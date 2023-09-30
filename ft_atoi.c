
#include "philo.h"

static int	ft_isspace(int c)
{
	return (c == '\t'
		||c == '\n'
		||c == '\v'
		||c == '\f'
		||c == '\r'
		||c == ' ');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		result;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*(str) - '0');
		str++;
	}

	return (result * sign);
}
