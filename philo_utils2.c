/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:14:22 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 17:59:08 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_data(t_philo *new, int i, char **argv)
{
	struct timeval	mytime;

	gettimeofday(&mytime, NULL);
	while (++i < ft_atoi(argv[1]))
	{
		new[i].philo_name = i + 1;
		new[i].philo_num = ft_atoi(argv[1]);
		new[i].time_to_die = ft_atoi(argv[2]);
		new[i].time_to_eat = ft_atoi(argv[3]);
		new[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5] != NULL)
			new[i].eat_number = ft_atoi(argv[5]);
		else
			new[i].eat_number = -1;
		new[i].lasteat_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		new[i].st_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		new[i].st_eat_time = 0;
		new[i].st_sl_time = 0;
		new[i].timeflag = 0;
	}
	return ;
}

void	mk_data2(t_philo *new, pthread_mutex_t *mutex, pthread_mutex_t *print)
{
	int	j;
	int	num;

	j = -1;
	num = new->philo_num;
	while (++j < num)
	{
		new[j].left = &mutex[j];
		if (j + 1 == num)
			new[j].right = &mutex[0];
		else
			new[j]. right = &mutex[j + 1];
		new[j].print = print;
		new[j].mutex = mutex;
	}
}

void	mk_data3(t_philo *new, int *fork)
{
	int	j;
	int	num;

	j = -1;
	num = new->philo_num;
	while (++j < num)
		new[j].fork = fork;
}

void	make_thread(t_philo *philo, char **argv, pthread_t	*pthread)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_create(&pthread[i], NULL, philo_to_do, (void *)&philo[i]);
	if (check_die(philo, ft_atoi(argv[1])) == 1)
	{
		i = -1;
		pthread_mutex_lock(philo->print);
		while (++i < philo[0].philo_num)
			philo[i].timeflag = 9;
		pthread_mutex_unlock(philo->print);
	}
}

void	signal_philo(t_philo *philo)
{
	int	i;

	while (1)
	{
		if (check_die(philo, philo->philo_num) == 1)
		{
			i = -1;
			pthread_mutex_lock(philo->print);
			while (++i < philo[0].philo_num)
				philo[i].timeflag = 9;
			pthread_mutex_unlock(philo->print);
			break ;
		}
	}
}
