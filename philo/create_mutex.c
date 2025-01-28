/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:26:22 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/05 18:45:16 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "philo.h"

pthread_mutex_t	*create_mutex_array(int nb)
{
	pthread_mutex_t	*mutex_array;
	int				i;

	i = -1;
	mutex_array = (pthread_mutex_t *) malloc
		(nb + 1000 * sizeof(pthread_mutex_t));
	while (++i < nb)
		pthread_mutex_init(&mutex_array[i], NULL);
	return (mutex_array);
}

void	assign_mutex(t_philo *arg, pthread_mutex_t *m_array)
{
	int		i;
	int		total;
	long	*time;
	long	*clock;

	i = 0;
	time = (long *)malloc(sizeof(long));
	clock = (long *)malloc(sizeof(long));
	total = arg[0].total - 1;
	arg[0].right_mutex = &m_array[0];
	arg[0].left_mutex = &m_array[total];
	*time = -1;
	arg[0].clock = clock;
	*clock = 0;
	arg[0].initial_time = time;
	while (++i <= total)
	{
		arg[i].right_mutex = &m_array[i];
		arg[i].left_mutex = &m_array[i - 1];
		arg[i].initial_time = time;
		arg[i].clock = clock;
	}
	start_clock(&arg[0]);
}

int	if_check(t_philo *info, int i)
{
	if (i >= info[0].total)
	{
		pthread_mutex_lock(info[0].dead_mutex);
		*info[0].dead = 1;
		pthread_mutex_unlock(info[0].dead_mutex);
		pthread_mutex_lock(info[0].end_flag_mutex);
		*info[0].endflag = 1;
		pthread_mutex_unlock(info[0].end_flag_mutex);
		return (1);
	}
	pthread_mutex_lock(info[0].end_flag_mutex);
	return (0);
}
