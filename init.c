
#include "philo.h"

void	init_data(t_data *data, t_args *args)
{
	struct timeval	tv;
	int				has_meal_goal;
	int				meal_goal;

	has_meal_goal = 0;
	meal_goal = 0;
	if (args->argc == 6)
	{
		has_meal_goal = 1;
		meal_goal = ft_atoi(args->argv[5]);
	}
	data->number_of_philo = ft_atoi(args->argv[1]);
	data->time_to_die = ft_atoi(args->argv[2]);
	data->time_to_eat = ft_atoi(args->argv[3]);
	data->time_to_sleep = ft_atoi(args->argv[4]);
	data->has_meal_goal = has_meal_goal;
	data->meal_goal = meal_goal;
	gettimeofday(&tv, NULL);
	data->start_time_sec = tv.tv_sec;
	data->start_time_usec = tv.tv_usec;
}

void	init_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		philo[i].id = i;
		philo[i].last_meal = 0;
		philo[i].meal_count = 0;
		i++;
	}
}

void	init_forks(pthread_mutex_t *fork, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

t_setup	*init_setup(t_philo *philo, pthread_mutex_t *fork, t_data *data)
{
	t_setup	*setup;
	int		i;

	setup = malloc(sizeof(t_setup) * data->number_of_philo);
	i = 0;
	while (i < data->number_of_philo)
	{
		setup[i].philo = &philo[i];
		setup[i].fork = fork;
		setup[i].data = data;
		i++;
	}
	return (setup);
}
