/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:33:56 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 17:52:01 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(t_philo *philo)
{
	if (philo->philo_name % 2 == 0)
	{
		philo_even(philo);
	}
	else
	{
		philo_odd(philo);
	}
}

void	philo_eat(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	philo->st_eat_time = now_time;
	pthread_mutex_lock(philo->print);
	if (philo->eat_number > 0)
		philo->eat_number--;
	philo->lasteat_time = now_time;
	if (philo->timeflag != 9)
		printf("%.f philo %d eating\n",
			now_time - philo->st_time, philo->philo_name);
	pthread_mutex_unlock(philo->print);
	while (1)
	{
		gettimeofday(&mytime, NULL);
		now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		if (now_time - philo->st_eat_time > philo->time_to_eat)
			break ;
		usleep(1000);
	}
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	philo->st_sl_time = now_time;
	pthread_mutex_lock(philo->print);
	if (philo->timeflag != 9)
		printf("%.f philo %d sleeping\n",
			now_time - philo->st_time, philo->philo_name);
	pthread_mutex_unlock(philo->print);
	while (1)
	{
		gettimeofday(&mytime, NULL);
		now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		if (now_time - philo->st_sl_time > philo->time_to_sleep)
			break ;
		usleep(1000);
	}
}

void	philo_think(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	pthread_mutex_lock(philo->print);
	if (philo->timeflag != 9)
		printf("%.f philo %d thinking\n",
			now_time - philo->st_time, philo->philo_name);
	pthread_mutex_unlock(philo->print);
	usleep(100);
}

void	*philo_to_do(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	if (philo->philo_name % 2 == 1)
		usleep(1000);
	if (philo->philo_num == 1)
		return (one_fork(philo));
	while (1)
	{
		pthread_mutex_lock(philo->print);
		if (philo->timeflag == 9)
			break ;
		pthread_mutex_unlock(philo->print);
		philo_fork(philo);
		philo_eat(philo);
		philo_put_down(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_mutex_unlock(philo->print);
	return (NULL);
}
