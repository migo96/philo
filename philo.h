/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:34:11 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 18:07:46 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				philo_name;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	double			lasteat_time;
	double			st_time;
	double			st_eat_time;
	double			st_sl_time;
	int				eat_number;
	int				timeflag;
	int				*fork;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
}t_philo;

void	fork_utils(t_philo *philo, int left, int right, int me);
int		check_die(t_philo *philo, int num);
int		argument_error(void);
int		ft_atoi(char *str);
void	*one_fork(t_philo *philo);
void	*philo_to_do(void *data);
int		check_argument(char **argv);
int		malloc_error(void);
void	make_data(t_philo *new, int i, char **argv);
void	make_thread(t_philo *philo, char **argv, pthread_t	*pthread);
void	free_join_pthread(t_philo *philo, pthread_t *pthread, char **argv);
int		argument_error(void);
void	signal_philo(t_philo *philo);
void	philo_odd(t_philo *philo);
void	philo_even(t_philo *philo);
void	philo_put_down(t_philo *philo);
void	mk_data2(t_philo *new, pthread_mutex_t *mutex, pthread_mutex_t *print);
void	mk_data3(t_philo *new, int *fork);
int		die_time_error(void);

#endif
