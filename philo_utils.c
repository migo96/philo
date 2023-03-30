/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:40:56 by migo              #+#    #+#             */
/*   Updated: 2023/03/30 17:09:50 by migo             ###   ########.fr       */
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

int	argument_error(void)
{
	printf("argument error\n");
	return (1);
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
		if (now_time - philo[i].lasteat_time == philo[i].time_to_die)
		{
			printf("%.f philo", now_time - philo[i].st_time);
			printf(" %d died\n", philo[i].philo_name);
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
	if (philo->fork[right] == 0)
	{
		philo->fork[me]++;
		printf("%.f philo", now_time - philo->st_time);
		printf(" %d has taken a right fork\n", philo->philo_name);
	}
	if (philo->fork[left] == 0)
	{
		philo->fork[me]++;
		printf("%.f philo", now_time - philo->st_time);
		printf(" %d has taken a left fork\n", philo->philo_name);
	}
}

void	one_fork(t_philo *philo)
{
	struct timeval	mytime;
	double			now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	if (philo->fork[0] == 0)
	{
		printf("%.f philo", now_time - philo->st_time);
		printf(" %d has taken a left fork\n", philo->philo_name);
		philo->fork[0] = 1;
	}
}