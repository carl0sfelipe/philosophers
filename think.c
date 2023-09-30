
#include "philo.h"

int	think(t_setup *setup)
{
	time_t	timestamp;

	pthread_mutex_lock(setup->gate);
	timestamp = get_timestamp(setup->data);
	if (*(setup->finish) == 0)
		printf("%ld %d is thinking\n", timestamp, setup->philo->id + 1);
	pthread_mutex_unlock(setup->gate);
	return (*(setup->finish));
}
