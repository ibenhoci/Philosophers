/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:23:02 by ibenhoci          #+#    #+#             */
/*   Updated: 2023/10/26 14:23:04 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *arg)
{
	int				nb;
	unsigned int	i;
	int				sign;

	i = 0;
	nb = 0;
	while (arg[i] == ' ' || arg[i] == '\n' || arg[i] == '\t'
		|| arg[i] == '\v' || arg[i] == '\r' || arg[i] == '\f')
		i++;
	sign = 1;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign *= (-1);
		i++;
	}
	if (arg[i] == '+' || arg[i] == '-')
		return (0);
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		nb = (nb * 10) + (arg[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	init_philo(t_arg args, t_data *philo, int id, t_full *arr)
{
	if (philo == NULL)
		return (1);
	philo->nb_philo = ft_atoi(args.argv[1]);
	philo->time_to_die = ft_atoi(args.argv[2]);
	philo->time_to_eat = ft_atoi(args.argv[3]);
	philo->time_to_sleep = ft_atoi(args.argv[4]);
	pthread_mutex_init(&philo->fork, NULL);
	gettimeofday(&philo->last_meal, NULL);
	philo->id = id;
	philo->head = arr;
	if (args.argc == 6)
	{
		philo->nbr_eat_max = ft_atoi(args.argv[5]);
		if (philo->nbr_eat_max < 0)
			return (1);
	}
	else
		philo->nbr_eat_max = -1;
	if (philo->time_to_die < 0 || philo->time_to_eat < 0
		|| philo->time_to_sleep < 0)
		return (1);
	gettimeofday(&philo->start_time, NULL);
	return (0);
}

void	launch(t_full *arr, t_arg args)
{
	int	i;

	i = -1;
	arr->dead_philo = 1;
	arr->philo = malloc(sizeof(t_data) * args.nb_philo);
	pthread_mutex_init(&arr->print, NULL);
	if (arr->philo == NULL)
		return ;
	while (++i < args.nb_philo)
	{
		init_philo(args, &arr->philo[i], i + 1, arr);
		pthread_create(&arr->philo[i].tid, NULL, routine, &arr->philo[i]);
	}
	check_status(arr, args);
	i = -1;
	while (++i < args.nb_philo)
		pthread_join(arr->philo[i].tid, NULL);
}

long	calculate(struct timeval start_time, struct timeval curr_time)
{
	return ((curr_time.tv_sec - start_time.tv_sec) * 1000
		+ (curr_time.tv_usec - start_time.tv_usec) / 1000);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_gettime();
	while ((ft_gettime() - start_time) < time_in_ms)
		usleep(200);
}
