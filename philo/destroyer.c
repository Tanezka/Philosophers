/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:26:37 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/05 18:32:47 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <stdlib.h>

void	destroy_philo_info(t_philo *philo_info)
{
	int	i;
	int	total;

	total = philo_info[0].total;
	i = -1;
	while (++i < total)
	{
		free(philo_info[i].times_ate);
		free(philo_info[i].eat_flag);
		free(philo_info[i].eat_mutex);
		pthread_mutex_destroy(philo_info[i].times_ate_mutex);
		free(philo_info[i].times_ate_mutex);
	}
	free(philo_info[0].clock);
	free(philo_info[0].initial_time);
	pthread_mutex_destroy(philo_info[0].dead_mutex);
	pthread_mutex_destroy(philo_info[0].time_mutex);
	free(philo_info[0].mu);
	free(philo_info);
}

void	destroy_mutexes(pthread_mutex_t *mutex_array, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
		pthread_mutex_destroy(&mutex_array[i]);
	free(mutex_array);
}
