/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fnc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:27:01 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/05 18:27:08 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void	timer_thread(t_philo *info)
{
	pthread_mutex_lock(info->eat_mutex);
	while (*(long *)info->eat_flag < info->time_to_die)
	{
		pthread_mutex_unlock(info->eat_mutex);
		my_usleep(1);
		pthread_mutex_lock(info->eat_mutex);
		(*info->eat_flag) += 1;
	}
	pthread_mutex_unlock(info->eat_mutex);
	pthread_mutex_lock(info->end_flag_mutex);
	*info->endflag = 1;
	pthread_mutex_unlock(info->end_flag_mutex);
	pthread_mutex_lock(info->dead_mutex);
	pthread_mutex_lock(info->clock_mutex);
	if (*info->dead != 1)
		printf("[%ld] %d died\n", *info->clock
			- *info->initial_time, info->index + 1);
	pthread_mutex_unlock(info->clock_mutex);
	*info->dead = 1;
	pthread_mutex_unlock(info->dead_mutex);
	return ;
}

void	action_printer(char *str, t_philo *info)
{
	pthread_mutex_lock(info->clock_mutex);
	pthread_mutex_lock(info->end_flag_mutex);
	if (*info->endflag != 1)
		printf("[%ld] %d %s\n", *info->clock - *info->initial_time,
			info->index + 1, str);
	pthread_mutex_unlock(info->end_flag_mutex);
	pthread_mutex_unlock(info->clock_mutex);
}

void	eat(t_philo *info)
{
	pthread_mutex_lock((*info).eat_mutex);
	*info->eat_flag = 0;
	pthread_mutex_unlock((*info).eat_mutex);
	pthread_mutex_lock((*info).times_ate_mutex);
	if (info->times_ate != NULL && *info->times_ate != 0)
		(*info->times_ate) -= 1;
	pthread_mutex_unlock((*info).times_ate_mutex);
	return ;
}

int	checker(t_philo *info)
{
	int	i;	

	i = 0;
	pthread_mutex_lock(info->end_flag_mutex);
	i = *info->endflag;
	pthread_mutex_unlock(info->end_flag_mutex);
	return (i);
}

void	routine(t_philo *arg)
{
	pthread_create(&arg->timer, NULL, (void *)timer_thread, arg);
	pthread_detach(arg->timer);
	my_usleep(arg->index % 2 * arg->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(arg->left_mutex);
		action_printer("has taken a fork", arg);
		pthread_mutex_lock(arg->right_mutex);
		action_printer("has taken a fork", arg);
		action_printer("is eating", arg);
		eat(arg);
		my_usleep(arg->time_to_eat);
		pthread_mutex_unlock(arg->right_mutex);
		pthread_mutex_unlock(arg->left_mutex);
		action_printer("is sleeping", arg);
		my_usleep(arg->time_to_sleep);
		action_printer("is thinking", arg);
		if (checker(arg) == 1)
			return ;
	}
	return ;
}
