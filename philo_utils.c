/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:40:56 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 18:05:38 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (str == NULL)
		return (-1);
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
	if (ft_atoi(argv[2]) == 0)
		return (2);
	if (ft_atoi(argv[5]) == 0)
		return (3);
	return (0);
}

int	check_eat_number(t_philo *philo, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (philo[i].eat_number != 0)
		{
			pthread_mutex_unlock(philo->print);
			return (0);
		}
	}
	pthread_mutex_unlock(philo->print);
	return (1);
}

int	check_die(t_philo *philo, int num)
{
	int				i;
	struct timeval	mytime;
	double			now_time;

	i = -1;
	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	pthread_mutex_lock(philo->print);
	while (++i < num)
	{
		if (now_time - philo[i].lasteat_time >= philo[i].time_to_die)
		{
			if (philo[i].timeflag != 9)
				printf("%.f philo %d died\n",
					now_time - philo[i].st_time, philo[i].philo_name);
			pthread_mutex_unlock(philo->print);
			return (1);
		}
	}
	return (check_eat_number(philo, num));
}

void	*one_fork(t_philo *philo)
{
	struct timeval	mytime;
	unsigned long	now_time;

	gettimeofday(&mytime, NULL);
	now_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
	pthread_mutex_lock(philo->print);
	printf("%.f philo %d has taken fork\n",
		now_time - philo->st_time, philo->philo_name);
	pthread_mutex_unlock(philo->print);
	return (NULL);
}
