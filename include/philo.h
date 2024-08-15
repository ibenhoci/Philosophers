/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhoci <ibenhoci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:23:22 by ibenhoci          #+#    #+#             */
/*   Updated: 2023/10/26 14:23:23 by ibenhoci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_full	t_full;
typedef struct s_data	t_data;
typedef struct s_data
{
	int				nb_philo;
	int				id;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nbr_eat_max;
	struct timeval	start_time;
	long long		start_time_long;
	struct timeval	last_meal;
	pthread_mutex_t	fork;
	pthread_t		tid;
	t_full			*head;
}					t_data;

typedef struct s_full
{
	t_data			*philo;
	int				dead_philo;
	pthread_mutex_t	print;
}	t_full;

typedef struct s_arg	t_arg;
typedef struct s_arg
{
	int		argc;
	char	**argv;
	int		nb_philo;
}	t_arg;

int			parse_args(int argc, char **argv, t_data *rules);
int			ft_atoi(char *arg);
int			init_philo(t_arg args, t_data *philo, int id, t_full *arr);
void		eat(t_data *philo);
void		*routine(void *var);
void		think(t_data *philo);
void		p_sleep(t_data *philo);
void		print_status(int id, char *msg, struct timeval start_time,
				t_data *philo);
void		launch(t_full *arr, t_arg args);
long		calculate(struct timeval start_time, struct timeval curr_time);
int			check_death(struct timeval last_meal, t_data *philo);
int			check_all_ate(t_full *arr, t_arg args);
void		eating_forks(t_data *philo, t_data *tmp, int ind);
void		check_status(t_full *arr, t_arg args);
void		ft_usleep(long int time_in_ms);
long long	ft_gettime(void);

#endif
