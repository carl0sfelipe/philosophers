/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:32:36 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/16 00:35:43 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	*vulture_monitor(void *arg)
{
	int		idx;
	t_setup	*config;
	time_t	timestamp;

	config = (t_setup *)arg;
	idx = 0;
	while (1)
	{
		timestamp = get_timestamp(config->data);
		if ((timestamp - config[idx].philo->last_meal) > \
			config->data->time_to_die)
		{
			printf("%ld %d died\n", timestamp, config[idx].philo->id + 1);
			*config->finish = 1;
			return (NULL);
		}
		idx = (idx + 1) % config->data->number_of_philo;
		usleep(1000);
	}
	return (NULL);
}

static void	*exist(void *arg)
{
	t_setup		*setup;
	t_setup		*config;

	config = (t_setup *)arg;
	setup = (t_setup *)arg;
	if ((setup->philo->id % 2) != 0)
		usleep(1000);
	while (42)
	{
		if (*config->finish == 1)
			return (NULL);
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
		i++;
	}
}

void	start_simulation(t_setup *setup)
{
	t_philo			*philo;
	pthread_mutex_t	gate;
	int				i;
	pthread_t		vulture_thread;

	setup->data->finish = 0;
	setup->data->finish_count = 0;
	pthread_mutex_init(&gate, NULL);
	i = 0;
	while (i < setup->data->number_of_philo)
	{
		philo = setup[i].philo;
		setup[i].finish = &setup->data->finish;
		setup[i].finish_count = &setup->data->finish_count;
		setup[i].gate = &gate;
		pthread_create(&philo->thread, NULL, exist, (void *)&setup[i]);
		i++;
	}
	pthread_create(&vulture_thread, NULL, vulture_monitor, (void *)setup);
	join_threads(setup);
}
