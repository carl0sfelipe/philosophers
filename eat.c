/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:34:24 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/14 20:34:26 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_first_fork(t_setup *setup, int id)
{
	int		i;
	time_t	timestamp;

	i = id;
	pthread_mutex_lock(&setup->fork[i]);
	pthread_mutex_lock(setup->gate);
	timestamp = get_timestamp(setup->data);
	if (*(setup->finish) == 0)
		printf("%ld %d has taken a fork\n", timestamp, id + 1);
	pthread_mutex_unlock(setup->gate);
	return (i);
}

static int	take_second_fork(t_setup *setup, int id)
{
	int		i;
	time_t	timestamp;

	i = (id + 1) % setup->data->number_of_philo;
	pthread_mutex_lock(&setup->fork[i]);
	pthread_mutex_lock(setup->gate);
	timestamp = get_timestamp(setup->data);
	if (*(setup->finish) == 0)
		printf("%ld %d has taken a fork\n", timestamp, id + 1);
	pthread_mutex_unlock(setup->gate);
	return (i);
}

int	eat(t_setup *setup)
{
	int		first_i;
	int		second_i;
	time_t	timestamp;

	first_i = take_first_fork(setup, setup->philo->id);
	if (setup->data->number_of_philo == 1)
	{
		smart_sleep(setup, setup->data->time_to_die);
		pthread_mutex_unlock(&setup->fork[first_i]);
		return (1);
	}
	second_i = take_second_fork(setup, setup->philo->id);
	pthread_mutex_lock(setup->gate);
	timestamp = get_timestamp(setup->data);
	setup->philo->last_meal = timestamp;
	if (*(setup->finish) == 0)
		printf("%ld %d is eating\n", timestamp, setup->philo->id + 1);
	pthread_mutex_unlock(setup->gate);
	smart_sleep(setup, setup->data->time_to_eat);
	setup->philo->meal_count++;
	pthread_mutex_unlock(&setup->fork[first_i]);
	pthread_mutex_unlock(&setup->fork[second_i]);
	return (*(setup->finish));
}
