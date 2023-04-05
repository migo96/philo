/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:46:16 by migo              #+#    #+#             */
/*   Updated: 2023/04/04 17:13:35 by migo             ###   ########.fr       */
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
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	int				*fork;

	new = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	mutex = malloc(sizeof(pthread_mutex_t) * 1);
	print = malloc(sizeof(pthread_mutex_t) * 1);
	fork = make_fork(argv);
	if (new == NULL || mutex == NULL || fork == NULL || print == NULL)
		return (new);
	pthread_mutex_init(mutex, NULL);
	pthread_mutex_init(print, NULL);
	make_data(new, i, argv);
	while (++i < ft_atoi(argv[1]))
	{
		new[i].fork = fork;
		new[i].mutex = mutex;
		new[i].print = print;
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
	int			i;

	argv = (char **)data;
	philo = make_philo(argv, -1);
	pthread = make_pthread(argv);
	if (philo == NULL || pthread == NULL)
		return (malloc_error);
	make_thread(philo, argv, pthread);
	while (1)
	{
		if (check_die(philo, ft_atoi(argv[1])) == 1)
		{
			i = -1;
			pthread_mutex_lock(philo->print);
			while (++i < philo[0].philo_num)
				philo[i].timeflag = 9;
			pthread_mutex_unlock(philo->print);
			break ;
		}
	}
	free_join_pthread(philo, pthread, argv);
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
