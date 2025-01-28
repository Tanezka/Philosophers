/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:26:13 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/05 18:30:18 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

t_philo	new_philo_info(char **av)
{
	t_philo	info;
	long	*times_ate;
	long	*eat_flag;
	int		dead_flag;

	eat_flag = (long *)malloc(sizeof(long));
	times_ate = (long *)malloc(sizeof(long) + 10);
	info.eat_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info.eat_mutex, NULL);
	info.times_ate_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info.times_ate_mutex, NULL);
	info.times_ate = times_ate;
	info.time_to_die = ft_atoi(av[2]);
	info.time_to_eat = ft_atoi(av[3]);
	info.time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		*info.times_ate = (long)ft_atoi(av[5]);
	info.total = ft_atoi(av[1]);
	info.eat_flag = eat_flag;
	info.dead = &dead_flag;
	dead_flag = 0;
	*eat_flag = -1;
	return (info);
}

t_philo	*create_philo_info(int nb, char **av, int *end_flag)
{
	t_philo			*philo_info;
	int				i;
	pthread_mutex_t	*mu;

	mu = (pthread_mutex_t *)malloc(4 * sizeof(pthread_mutex_t));
	pthread_mutex_init(&mu[2], NULL);
	pthread_mutex_init(&mu[0], NULL);
	pthread_mutex_init(&mu[1], NULL);
	pthread_mutex_init(&mu[3], NULL);
	i = -1;
	philo_info = (t_philo *)malloc(nb + 1000 * sizeof(t_philo));
	while (++i < nb)
	{
		philo_info[i] = new_philo_info(av);
		philo_info[i].index = i;
		philo_info[i].endflag = end_flag;
		philo_info[i].dead_mutex = &mu[0];
		philo_info[i].time_mutex = &mu[1];
		philo_info[i].end_flag_mutex = &mu[2];
		philo_info[i].clock_mutex = &mu[3];
	}
	philo_info[0].mu = mu;
	return (philo_info);
}
