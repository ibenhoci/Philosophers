/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:22:43 by ibenhoci          #+#    #+#             */
/*   Updated: 2023/10/26 14:22:45 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_full			*arr;
	t_arg			args;

	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
			|| ft_atoi(argv[4]) < 0 || ft_atoi(argv[1]) < 0)
			return (0);
		if (argc == 6 && ft_atoi(argv[5]) < 0)
			return (0);
		args.nb_philo = ft_atoi(argv[1]);
		args.argc = argc;
		args.argv = argv;
		arr = malloc(sizeof(t_full));
		launch(arr, args);
		argc = -1;
		while (++argc < args.nb_philo)
			pthread_mutex_destroy(&arr->philo[argc].fork);
	}
	return (0);
}
