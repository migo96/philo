/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:24:32 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 17:53:02 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_odd(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;
	int				me;

	me = philo->philo_name - 1;
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->print);
	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	if (philo->timeflag != 9)
		printf("%.f philo %d has taken fork\n",
			now_time - philo->st_time, philo->philo_name);
	philo->fork[me]++;
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	philo->fork[me]++;
	pthread_mutex_unlock(philo->print);
}

void	philo_even(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;
	int				me;

	me = philo->philo_name - 1;
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->print);
	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	if (philo->timeflag != 9)
		printf("%.f philo %d has taken fork\n",
			now_time - philo->st_time, philo->philo_name);
	philo->fork[me]++;
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->print);
	philo->fork[me]++;
	pthread_mutex_unlock(philo->print);
}

void	philo_put_down(t_philo *philo)
{
	int				me;

	me = philo->philo_name - 1;
	pthread_mutex_lock(philo->print);
	philo->fork[me] = 0;
	pthread_mutex_unlock(philo->print);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}
