
#include "philo.h"

static int	validate_args(t_args *args)
{
	if (args->argc < 5 || args->argc > 6)
		return (1);
	else if (!(has_only_int(args->argc, args->argv)))
		return (2);
	else if (ft_atoi(args->argv[1]) < 1)
		return (3);
	else if (is_out_of_bounds(args->argc, args->argv))
		return (4);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	t_setup			*setup;

	args.argc = argc;
	args.argv = argv;
	if (validate_args(&args))
	{
		printf("./philo: Invalid arguments.\n");
		return (1);
	}
	init_data(&data, &args);
	philo = malloc(sizeof(t_philo) * data.number_of_philo);
	init_philo(philo, &data);
	fork = malloc(sizeof(pthread_mutex_t) * data.number_of_philo);
	init_forks(fork, &data);
	setup = init_setup(philo, fork, &data);
	start_simulation(setup);
	free(philo);
	free(fork);
	free(setup);
	return (0);
}
