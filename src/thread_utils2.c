/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:22:56 by ibenhoci          #+#    #+#             */
/*   Updated: 2023/10/26 14:22:58 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(struct timeval last_meal, t_data *philo)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	if (calculate(last_meal, curr_time) >= philo->time_to_die
		&& philo->nbr_eat_max != -2)
	{
		print_status(philo->id, "died", philo->start_time, philo);
		philo->head->dead_philo = 0;
		return (1);
	}
	return (0);
}

int	check_all_ate(t_full *arr, t_arg args)
{
	int	i;

	i = -1;
	while (++i < args.nb_philo)
	{
		if (arr->philo[i].nbr_eat_max != -2)
			return (0);
	}
	return (1);
}

void	eating_forks(t_data *philo, t_data *tmp, int ind)
{
	pthread_mutex_lock(&philo->fork);
	print_status(ind + 1, "has taken a fork", philo->start_time, philo);
	pthread_mutex_lock(&tmp->fork);
	print_status(ind + 1, "has taken a fork", philo->start_time, philo);
}

void	check_status(t_full *arr, t_arg args)
{
	int	i;

	i = 0;
	while (arr->dead_philo)
	{
		if (args.argc == 6)
		{
			if (check_all_ate(arr, args))
				return ;
		}
		check_death(arr->philo[i].last_meal, &arr->philo[i]);
		i++;
		i %= args.nb_philo;
	}
}

long long	ft_gettime(void)
{
	struct timeval	time_value;
	long long		time;

	gettimeofday(&time_value, NULL);
	time = time_value.tv_sec * 1000 + time_value.tv_usec / 1000;
	return (time);
}
