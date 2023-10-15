/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_only_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csiqueir <csiqueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:33:31 by csiqueir          #+#    #+#             */
/*   Updated: 2023/10/14 20:33:33 by csiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	has_only_int(int argc, char **argv)
{
	int		i;

	while ((argc - 1) > 0)
	{
		i = 0;
		while (argv[argc - 1][i])
		{
			if (!(ft_isdigit(argv[argc - 1][i])))
				return (0);
			i++;
		}
		argc--;
	}
	return (1);
}
