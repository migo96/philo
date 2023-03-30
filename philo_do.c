/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:33:56 by migo              #+#    #+#             */
/*   Updated: 2023/03/30 17:14:28 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(t_philo *philo, pthread_mutex_t mutex, int flag)
{
	int	i;

	i = philo->philo_name - 1;
	pthread_mutex_lock(&mutex);
	if (flag == 1)
	{
		if (philo->philo_num == 1)
		{
			one_fork(philo);
			return ;
		}
		if (i == 0)
			fork_utils(philo, philo->philo_num - 1, i + 1, i);
		else if (i == philo->philo_num - 1)
			fork_utils(philo, i - 1, 0, i);
		else
			fork_utils(philo, i - 1, i + 1, i);
	}
	else if (philo->fork[i] == 2)
		philo->fork[i] = 0;
	pthread_mutex_unlock(&mutex);
}

void	philo_eat(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	if (philo->fork[philo->philo_name - 1] == 2)
		philo->st_eat_time = now_time;
	else
		return ;
	printf("%.f philo", now_time - philo->st_time);
	printf(" %d eating\n", philo->philo_name);
	philo->lasteat_time = now_time;
	philo->timeflag = 1;
	while (1)
	{
		gettimeofday(&mytime, NULL);
		now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		if (now_time - philo->st_eat_time > philo->time_to_eat)
		{
			philo->lasteat_time = now_time;
			break ;
		}
	}
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	if (philo->timeflag == 1)
		philo->st_sl_time = now_time;
	else
		return ;
	printf("%.f philo", now_time - philo->st_time);
	printf(" %d sleeping\n", philo->philo_name);
	philo->timeflag = 2;
	while (1)
	{
		gettimeofday(&mytime, NULL);
		now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		if (now_time - philo->st_sl_time > philo->time_to_sleep)
			break ;
	}
}

void	philo_think(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	if (philo->timeflag == 2)
	{
		philo->timeflag = 0;
		printf("%.f philo", now_time - philo->st_time);
		printf(" %d thinking\n", philo->philo_name);
	}
}

void	*philo_to_do(void *data)
{
	t_philo			*philo;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	philo = (t_philo *)data;
	while (1)
	{
		philo_fork(philo, mutex, 1);
		philo_eat(philo);
		philo_fork(philo, mutex, 0);
		philo_sleep(philo);
		philo_think(philo);
	}
}