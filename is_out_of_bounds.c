/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_out_of_bounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:33:14 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/14 20:33:17 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

static int	check_max_limit(char *number)
{
	const char	*max;
	int			i;

	max = "2147483647";
	i = 0;
	while (number[i])
	{
		if ((number[i]) - '0' > max[i] - '0')
			return (1);
		if ((number[i]) - '0' < max[i] - '0')
			return (0);
		i++;
	}
	return (0);
}

int	is_out_of_bounds(int argc, char **argv)
{
	while ((argc - 1) > 0)
	{
		if (ft_strlen(argv[argc - 1]) > 10)
			return (1);
		else if (ft_strlen(argv[argc - 1]) == 10)
			return (check_max_limit(argv[argc - 1]));
		argc--;
	}
	return (0);
}
