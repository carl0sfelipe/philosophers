/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:32:46 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/14 20:32:49 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_sleep(t_setup *setup)
{
	time_t	timestamp;

	pthread_mutex_lock(setup->gate);
	timestamp = get_timestamp(setup->data);
	if (*(setup->finish) == 0)
		printf("%ld %d is sleeping\n", timestamp, setup->philo->id + 1);
	pthread_mutex_unlock(setup->gate);
	smart_sleep(setup, setup->data->time_to_sleep);
	return (*(setup->finish));
}
