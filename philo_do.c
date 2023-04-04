/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:33:56 by migo              #+#    #+#             */
/*   Updated: 2023/04/04 16:57:22 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(t_philo *philo, int flag)
{
	int	i;

	i = philo->philo_name - 1;
	pthread_mutex_lock(philo->mutex);
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
	pthread_mutex_unlock(philo->mutex);
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
	if (philo->timeflag != 9)
		printf("%.f philo %d eating\n",
			now_time - philo->st_time, philo->philo_name);
	philo->timeflag = 1;
	philo->lasteat_time = now_time;
	while (1)
	{
		gettimeofday(&mytime, NULL);
		now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		if (now_time - philo->st_eat_time > philo->time_to_eat * 0.993)
		{
			break ;
		}
		usleep(1000);
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
	if (philo->timeflag != 9)
		printf("%.f philo %d sleeping\n",
			now_time - philo->st_time, philo->philo_name);
	philo->timeflag = 2;
	while (1)
	{
		gettimeofday(&mytime, NULL);
		now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		if (now_time - philo->st_sl_time > philo->time_to_sleep * 0.993)
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
	if (philo->timeflag == 2)
	{
		philo->timeflag = 0;
		if (philo->timeflag != 9)
			printf("%.f philo %d thinking\n",
				now_time - philo->st_time, philo->philo_name);
	}
}

void	*philo_to_do(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	if (philo->philo_name % 2 == 1)
		usleep(10000);
	while (1)
	{
		if (philo->timeflag == 9)
			break ;
		philo_fork(philo, 1);
		if (philo->timeflag == 9)
			break ;
		philo_eat(philo);
		if (philo->timeflag == 9)
			break ;
		philo_fork(philo, 0);
		if (philo->timeflag == 9)
			break ;
		philo_sleep(philo);
		if (philo->timeflag == 9)
			break ;
		philo_think(philo);
	}
	return (NULL);
}