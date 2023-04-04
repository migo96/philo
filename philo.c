/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:46:16 by migo              #+#    #+#             */
/*   Updated: 2023/04/04 16:56:47 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*make_fork(char **argv)
{
	int	i;
	int	*fork;

	i = 0;
	fork = malloc(sizeof(int) * ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		fork[i] = 0;
		i++;
	}
	return (fork);
}

t_philo	*make_philo(char **argv, int i)
{
	t_philo			*new;
	struct timeval	mytime;
	pthread_mutex_t	*mutex;
	int				*fork;

	gettimeofday(&mytime, NULL);
	new = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	mutex = malloc(sizeof(pthread_mutex_t) * 1);
	fork = make_fork(argv);
	if (new == NULL || mutex == NULL || fork == NULL)
		return (new);
	pthread_mutex_init(mutex, NULL);
	while (++i < ft_atoi(argv[1]))
	{
		new[i].philo_name = i + 1;
		new[i].philo_num = ft_atoi(argv[1]);
		new[i].time_to_die = (double)ft_atoi(argv[2]);
		new[i].time_to_eat = (double)ft_atoi(argv[3]);
		new[i].time_to_sleep = (double)ft_atoi(argv[4]);
		new[i].lasteat_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		new[i].st_time = mytime.tv_sec * 1000 + (mytime.tv_usec / 1000);
		new[i].st_eat_time = 0;
		new[i].st_sl_time = 0;
		new[i].timeflag = 0;
		new[i].fork = fork;
		new[i].mutex = mutex;
	}
	return (new);
}

pthread_t	*make_pthread(char **argv)
{
	pthread_t	*new;

	new = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	return (new);
}

void	*table_to_sit(void *data)
{
	char		**argv;
	t_philo		*philo;
	pthread_t	*pthread;
	pthread_mutex_t	mutex;
	int			i;

	argv = (char **)data;
	philo = make_philo(argv, -1);
	pthread = make_pthread(argv);
	pthread_mutex_init(&mutex, NULL);
	if (philo == NULL || pthread == NULL)
		return (malloc_error);
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_create(&pthread[i], NULL, philo_to_do, (void *)&philo[i]);
	while (1)
	{
		if (check_die(philo, ft_atoi(argv[1])) == 1)
		{
			pthread_mutex_lock(&mutex);
			i = -1;
			while (++i < philo[0].philo_num)
				philo[i].timeflag = 9;
			break ;
			pthread_mutex_unlock(&mutex);
		}
	}
	i = -1;
	while (++i < ft_atoi(argv[1]))
		pthread_join(pthread[i], NULL);
	free (philo->mutex);
	free (philo->fork);
	free (philo);
	free (pthread);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	pthread;

	if (argc != 5 && argc != 6)
		return (argument_error());
	if (check_argument(argv))
		return (argument_error());
	pthread_create(&pthread, NULL, table_to_sit, (void *)argv);
	pthread_join(pthread, NULL);
	return (0);
}
