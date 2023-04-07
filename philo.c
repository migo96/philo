/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:46:16 by migo              #+#    #+#             */
/*   Updated: 2023/04/07 17:22:03 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_philo(t_philo *philo)
{
	free (philo);
	return (NULL);
}

int	free_philo_mutex(t_philo *philo)
{
	free (philo->mutex);
	free (philo);
	return (malloc_error());
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

	new = (t_philo *) malloc(sizeof(t_philo) * num);
	if (new == NULL)
		return (NULL);
	mutex = malloc(sizeof(pthread_mutex_t) * num);
	if (mutex == NULL)
		return (free_philo(new));
	print = malloc(sizeof(pthread_mutex_t) * 1);
	while (++i < num)
		pthread_mutex_init(&mutex[i], NULL);
	pthread_mutex_init(print, NULL);
	make_data(new, j, argv);
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
	return (new);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	pthread_t	*pthread;

	if (argc != 5 && argc != 6)
		return (argument_error());
	if (check_argument(argv))
		return (argument_error());
	philo = make_philo(argv, -1, -1, ft_atoi(argv[1]));
	if (philo == NULL)
		return (malloc_error());
	pthread = make_pthread(argv);
	if (pthread == NULL)
		free_philo_mutex(philo);
	make_thread(philo, argv, pthread);
	signal_philo(philo);
	free_join_pthread(philo, pthread, argv);
	return (0);
}
