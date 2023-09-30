
#include "philo.h"

static void	*monitor(void *arg)
{
	t_setup			*setup;
	time_t			timestamp;

	setup = (t_setup *)arg;
	while (42)
	{
		pthread_mutex_lock(setup->gate);
		if (*(setup->finish) == 1)
		{
			pthread_mutex_unlock(setup->gate);
			break ;
		}
		timestamp = get_timestamp(setup->data);
		if ((timestamp - setup->philo->last_meal) > setup->data->time_to_die)
		{
			if (*(setup->finish) == 0)
				printf("%ld %d died\n", timestamp, setup->philo->id + 1);
			*(setup->finish) = 1;
		}
		pthread_mutex_unlock(setup->gate);
	}
	return (NULL);
}

static void	*exist(void *arg)
{
	t_setup			*setup;

	setup = (t_setup *)arg;
	if ((setup->philo->id % 2) != 0)
		usleep(1000);
	while (42)
	{
		if (think(setup))
			break ;
		if (eat(setup))
			break ;
		if (check_meal_count(setup))
			break ;
		if (my_sleep(setup))
			break ;
	}
	return (NULL);
}

static void	join_threads(t_setup *setup)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < setup->data->number_of_philo)
	{
		philo = setup[i].philo;
		pthread_join(philo->thread, NULL);
		pthread_join(philo->monitor, NULL);
		i++;
	}
}

void	start_simulation(t_setup *setup)
{
	t_philo			*philo;
	int				finish;
	int				finish_count;
	pthread_mutex_t	gate;
	int				i;

	finish = 0;
	finish_count = 0;
	pthread_mutex_init(&gate, NULL);
	i = 0;
	while (i < setup->data->number_of_philo)
	{
		philo = setup[i].philo;
		setup[i].finish = &finish;
		setup[i].finish_count = &finish_count;
		setup[i].gate = &gate;
		pthread_create(&philo->thread, NULL, exist, (void *)&setup[i]);
		pthread_create(&philo->monitor, NULL, monitor, (void *)&setup[i]);
		i++;
	}
	join_threads(setup);
}
