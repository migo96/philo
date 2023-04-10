/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:00:37 by migo              #+#    #+#             */
/*   Updated: 2023/04/10 18:07:34 by migo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_error(void)
{
	printf("malloc error\n");
	return (1);
}

int	argument_error(void)
{
	printf("argument error\n");
	return (1);
}

int	die_time_error(void)
{
	printf("0 philo 1 is died");
	return (1);
}
