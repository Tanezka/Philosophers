/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:26:00 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/02 17:33:47 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	my_usleep(int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		usleep(1000);
		i++;
	}
}

void	my_clock(t_philo *info)
{
	pthread_mutex_lock(info->dead_mutex);
	while (*info->dead != 1)
	{
		pthread_mutex_unlock(info->dead_mutex);
		usleep(1000);
		pthread_mutex_lock(info->clock_mutex);
		(*info->clock)++;
		pthread_mutex_unlock(info->clock_mutex);
		pthread_mutex_lock(info->dead_mutex);
	}
	pthread_mutex_unlock(info->dead_mutex);
	return ;
}

void	start_clock(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, (void *)my_clock, philo) < 0)
		return ;
	pthread_detach(thread);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	ret;

	sign = 1;
	ret = 0;
	while (*str == ' ' || *str == '\f' || *str == '\v'
		|| *str == '\t' || *str == '\n' || *str == '\r')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ((*str) >= '0' && (*str) <= '9')
	{
		ret = (ret * 10) + *str - '0';
		str++;
	}
	return (ret * sign);
}
