/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:32:24 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/14 20:32:28 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_args
{
	int		argc;
	char	**argv;
}			t_args;

typedef struct s_data
{
	int			number_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			has_meal_goal;
	int			meal_goal;
	time_t		start_time_sec;
	suseconds_t	start_time_usec;
	int			finish;
	int			finish_count;
}				t_data;

typedef struct s_philo
{
	int			id;
	time_t		last_meal;
	int			meal_count;
	pthread_t	thread;
}				t_philo;

typedef struct s_setup
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	t_data			*data;
	int				*finish;
	int				*finish_count;
	pthread_mutex_t	*gate;
}					t_setup;

int		has_only_int(int argc, char **argv);
int		is_out_of_bounds(int argc, char **argv);

void	init_data(t_data *data, t_args *args);
void	init_philo(t_philo *philo, t_data *data);
void	init_forks(pthread_mutex_t *fork, t_data *data);
t_setup	*init_setup(t_philo *philo, pthread_mutex_t *fork, t_data *data);

void	start_simulation(t_setup *setup);

int		think(t_setup *setup);
int		eat(t_setup *setup);
int		my_sleep(t_setup *setup);

void	smart_sleep(t_setup *setup, time_t time);
int		check_meal_count(t_setup *setup);
int		ft_atoi(const char *arr);
time_t	get_timestamp(t_data *data);

#endif
