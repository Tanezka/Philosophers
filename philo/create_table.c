/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:26:29 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/02 17:41:36 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

pthread_t	*create_table(int nb, t_philo *philo_info)
{
	int			i;
	pthread_t	*table;

	table = (pthread_t *)malloc(nb + 1000 * sizeof(pthread_t));
	i = -1;
	pthread_mutex_lock(philo_info->clock_mutex);
	*philo_info[0].initial_time = *philo_info[0].clock -1;
	pthread_mutex_unlock(philo_info->clock_mutex);
	while (++i < nb)
	{
		philo_info[i].current = &table[i];
		*philo_info[i].eat_flag = -1;
		if (pthread_create(&table[i], NULL
				, (void *)routine, &philo_info[i]) < 0)
			return (NULL);
	}
	return (table);
}
