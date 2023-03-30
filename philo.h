/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:34:11 by migo              #+#    #+#             */
/*   Updated: 2023/03/30 17:00:23 by migo             ###   ########.fr       */
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
	double			time_to_die;
	double			time_to_eat;
	double			time_to_sleep;
	double			lasteat_time;
	double			st_time;
	double			st_eat_time;
	double			st_sl_time;
	int				timeflag;
	int				*fork;
}t_philo;

void	fork_utils(t_philo *philo, int left, int right, int me);
int		check_die(t_philo *philo, int num);
int		argument_error(void);
int		ft_atoi(char *str);
void	one_fork(t_philo *philo);
void	*philo_to_do(void *data);

#endif
