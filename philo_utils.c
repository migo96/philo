/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:40:56 by migo              #+#    #+#             */
/*   Updated: 2023/04/04 15:23:47 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num *= 10;
		num = num + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (num);
}

int	check_argument(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) == 0)
		return (1);
	return (0);
}

int	check_die(t_philo *philo, int num)
{
	int				i;
	struct timeval	mytime;
	double			now_time;

	i = 0;
	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	while (i < num)
	{
		if (now_time - philo[i].lasteat_time >= philo[i].time_to_die)
		{
			pthread_mutex_lock(philo->print);
			if (philo[i].lasteat_time != 0 && philo[i].timeflag != 9)
			{
				printf("%.f philo", now_time - philo[i].st_time);
				printf(" %d died\n", philo[i].philo_name);
			}
			pthread_mutex_unlock(philo->print);
			return (1);
		}
		i++;
	}
	return (0);
}

void	fork_utils(t_philo *philo, int left, int right, int me)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	pthread_mutex_lock(philo->print);
	if (philo->fork[right] == 0 && philo->fork[me] == 0 && philo->timeflag != 9)
	{
		printf("%.f philo %d has taken a right fork\n",
			now_time - philo->st_time, philo->philo_name);
			philo->fork[me]++;
	}
	if (philo->fork[left] == 0 && philo->fork[me] == 1 && philo->timeflag != 9)
	{
		printf("%.f philo %d has taken a left fork\n",
			now_time - philo->st_time, philo->philo_name);
			philo->fork[me]++;
	}
	pthread_mutex_unlock(philo->print);
}

void	one_fork(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	pthread_mutex_lock(philo->print);
	if (philo->fork[0] == 0 && philo->timeflag != 9)
	{
		printf("%.f philo %d has taken a left fork\n",
			now_time - philo->st_time, philo->philo_name);
		philo->fork[0] = 1;
	}
	pthread_mutex_unlock(philo->print);
}
