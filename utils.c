/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:32:57 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/14 20:33:00 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_count(t_setup *setup)
{
	if (!setup->data->has_meal_goal)
		return (*(setup->finish));
	if (setup->philo->meal_count >= setup->data->meal_goal)
		*(setup->finish_count) += 1;
	if (*(setup->finish_count) >= setup->data->number_of_philo)
		*(setup->finish) = 1;
	return (*(setup->finish));
}

void	smart_sleep(t_setup *setup, time_t time)
{
	time_t	start;

	start = get_timestamp(setup->data);
	while (42)
	{
		pthread_mutex_lock(&setup->gate[0]);
		if ((get_timestamp(setup->data) - start) >= time
			|| *(setup->finish) == 1)
		{
			pthread_mutex_unlock(&setup->gate[0]);
			break ;
		}
		pthread_mutex_unlock(&setup->gate[0]);
		usleep(250);
	}
}

time_t	get_timestamp(t_data *data)
{
	time_t			start_time;
	time_t			current_time;
	time_t			timestamp;
	struct timeval	current;

	gettimeofday(&current, NULL);
	current_time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	start_time = (data->start_time_sec * 1000) + (data->start_time_usec / 1000);
	timestamp = current_time - start_time;
	return (timestamp);
}
