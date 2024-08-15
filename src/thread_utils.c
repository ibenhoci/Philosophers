/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:22:50 by ibenhoci          #+#    #+#             */
/*   Updated: 2023/10/26 14:22:52 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_data *philo)
{
	int		ind;
	t_data	*tmp;

	ind = philo->id - 1;
	if ((ind + 1) < philo->nb_philo)
		tmp = philo + 1;
	else
		tmp = philo - ind;
	eating_forks(philo, tmp, ind);
	gettimeofday(&philo->last_meal, NULL);
	print_status(ind + 1, "is eating", philo->start_time, philo);
	ft_usleep(philo->time_to_eat + 1);
	pthread_mutex_unlock(&tmp->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	print_status(int id, char *msg, struct timeval start_time,
	t_data *philo)
{
	struct timeval	curr_time;
	long			val;
	pthread_mutex_t	*mut;

	if (!philo->head->dead_philo)
		return ;
	mut = &philo->head->print;
	gettimeofday(&curr_time, NULL);
	val = calculate(start_time, curr_time);
	pthread_mutex_lock(mut);
	if (!philo->head->dead_philo)
		return ;
	printf("%ld %d %s\n", val, id, msg);
	pthread_mutex_unlock(mut);
}

void	p_sleep(t_data *philo)
{
	print_status(philo->id, "is sleeping", philo->start_time, philo);
	ft_usleep(philo->time_to_sleep);
}

void	think(t_data *philo)
{
	print_status(philo->id, "is thinking", philo->start_time, philo);
}

void	*routine(void *var)
{
	t_data			*philo;
	int				times_ate;

	times_ate = 0;
	philo = (t_data *)var;
	if (philo->nb_philo == 1)
		print_status(philo->id, "has taken a fork",
			philo->start_time, philo);
	else
	{
		if (philo->id % 2 == 0)
			ft_usleep(30);
		while ((times_ate < philo->nbr_eat_max || philo->nbr_eat_max == -1)
			&& philo->head->dead_philo)
		{
			eat(philo);
			times_ate++;
			p_sleep(philo);
			think(philo);
		}
		if (times_ate == philo->nbr_eat_max)
			philo->nbr_eat_max = -2;
	}
	return (NULL);
}
