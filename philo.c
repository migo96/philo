/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:46:16 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 18:06:52 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_join_pthread(t_philo *philo, pthread_t *pthread, char **argv)
{
	int	i;
	int	num;

	num = ft_atoi(argv[1]);
	i = -1;
	while (++i < num)
		pthread_join(pthread[i], NULL);
	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&philo->mutex[i]);
	philo->eat_number = 5;
	free (philo->mutex);
	free (philo);
	free (pthread);
	return ;
}

pthread_t	*make_pthread(char **argv)
{
	pthread_t	*new;

	new = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	return (new);
}

int	*make_fork(char **argv)
{
	int	i;
	int	*fork;

	i = 0;
	fork = malloc(sizeof(int) * ft_atoi(argv[1]));
	if (fork == NULL)
		return (NULL);
	while (i < ft_atoi(argv[1]))
	{
		fork[i] = 0;
		i++;
	}
	return (fork);
}

t_philo	*make_philo(char **argv, int i, int j, int num)
{
	t_philo			*new;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	int				*fork;

	new = (t_philo *) malloc(sizeof(t_philo) * num);
	if (new == NULL)
		return (NULL);
	mutex = malloc(sizeof(pthread_mutex_t) * num);
	if (mutex == NULL)
		return (new);
	print = malloc(sizeof(pthread_mutex_t) * 1);
	if (print == NULL)
		return (new);
	fork = make_fork(argv);
	if (fork == NULL)
		return (NULL);
	while (++i < num)
		pthread_mutex_init(&mutex[i], NULL);
	pthread_mutex_init(print, NULL);
	make_data(new, j, argv);
	mk_data2(new, mutex, print);
	mk_data3(new, fork);
	return (new);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*pthread;

	if (argc != 5 && argc != 6)
		return (argument_error());
	if (check_argument(argv) == 1)
		return (argument_error());
	if (check_argument(argv) == 2)
		return (die_time_error());
	if (check_argument(argv) == 3)
		return (1);
	philo = make_philo(argv, -1, -1, ft_atoi(argv[1]));
	if (philo == NULL || philo->mutex == NULL
		|| philo->print == NULL || philo->fork == NULL)
		return (malloc_error());
	pthread = make_pthread(argv);
	if (pthread == NULL)
		return (malloc_error());
	make_thread(philo, argv, pthread);
	signal_philo(philo);
	free_join_pthread(philo, pthread, argv);
	return (0);
}
