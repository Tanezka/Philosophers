/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaraaga <tkaraaga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:15:29 by tkaraaga          #+#    #+#             */
/*   Updated: 2023/11/05 18:44:27 by tkaraaga         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_philo
{
	long				*initial_time;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_die;
	long				*clock;
	int					index;
	long				total;
	long				*times_ate;
	long				*eat_flag;
	int					*dead;
	int					*endflag;
	pthread_mutex_t		*eat_mutex;
	pthread_mutex_t		*right_mutex;
	pthread_mutex_t		*left_mutex;
	pthread_mutex_t		*time_mutex;
	pthread_mutex_t		*dead_mutex;
	pthread_mutex_t		*clock_mutex;
	pthread_mutex_t		*end_flag_mutex;
	pthread_mutex_t		*times_ate_mutex;
	pthread_mutex_t		*mu;
	pthread_t			timer;
	pthread_t			*current;
}						t_philo;

int				if_check(t_philo *info, int i);

void			my_usleep(int nb);

void			my_clock(t_philo *info);

void			start_clock(t_philo *philo);

int				ft_atoi(const char *str);

pthread_t		*create_table(int nb, t_philo *philo_info);

void			timer_thread(t_philo *info);

void			routine(t_philo *arg);// değiş bunu

void			destroy_philo_info(t_philo *philo_info);

pthread_mutex_t	*create_mutex_array(int nb);

void			assign_mutex(t_philo *arg, pthread_mutex_t *m_array);

void			destroy_mutexes(pthread_mutex_t *mutex_array, int nb);

t_philo			new_philo_info(char **av);

t_philo			*create_philo_info(int nb, char **av, int *end_flag);

#endif
