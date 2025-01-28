/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:26:45 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/05 18:44:05 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"
#include <stdio.h>

void	wait_thread(pthread_t *table, pthread_t eat)
{
	int	i;

	i = -1;
	if (table[1] == NULL)
		my_usleep(1000);
	else
	{
		while (table[++i] != NULL)
			pthread_join(table[i], NULL);
	}
	if (eat != NULL)
		pthread_join(eat, NULL);
}

int	check_arguments(char **av)
{
	int	i;
	int	j;

	j = 0;
	while (av[++j])
	{
		i = -1;
		while (av[j][++i])
		{
			if (av[j][i] > '9' || av[j][i] < '0')
				return (1);
		}
	}
	return (0);
}

void	eat_check(t_philo *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(info[0].end_flag_mutex);
	while (*info[0].endflag != 1)
	{
		pthread_mutex_unlock(info[0].end_flag_mutex);
		while (i < info[0].total)
		{
			pthread_mutex_lock(info[i].times_ate_mutex);
			if (*info[i].times_ate == 0)
			{
				pthread_mutex_unlock(info[i].times_ate_mutex);
				i++;
			}
			else
			{
				pthread_mutex_unlock(info[i].times_ate_mutex);
				break ;
			}
		}
		if (if_check(info, i) == 1)
			break ;
	}
	pthread_mutex_unlock(info[0].end_flag_mutex);
}

pthread_t	eat_thread(t_philo *info, char **av)
{
	pthread_t	thread;

	if (av[5] == NULL)
		return (NULL);
	if (pthread_create(&thread, NULL, (void *)eat_check, info) < 0)
		return (NULL);
	return (thread);
}

int	main(int ac, char **av)
{
	int					*end_flag;
	t_philo				*philo_info;
	pthread_mutex_t		*mutex_array;
	pthread_t			*table;

	if ((ac != 5 && ac != 6) || check_arguments(av) == 1
		|| ft_atoi(av[1]) == 0 || (av[5] != NULL && ft_atoi(av[5]) == 0))
	{
		printf("Error\n");
		return (0);
	}
	end_flag = (int *)malloc(sizeof(int));
	*end_flag = 0;
	mutex_array = create_mutex_array((int)ft_atoi(av[1]));
	philo_info = create_philo_info((int)ft_atoi(av[1]), av, end_flag);
	assign_mutex(philo_info, mutex_array);
	table = create_table((int)ft_atoi(av[1]), philo_info);
	wait_thread(table, eat_thread(philo_info, av));
	my_usleep(1000);
	destroy_mutexes(mutex_array, philo_info[0].total);
	destroy_philo_info(philo_info);
	free(table);
	free(end_flag);
}
