/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migo <migo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:00:37 by migo              #+#    #+#             */
/*   Updated: 2023/04/07 11:49:08 by migo             ###   ########.fr       */
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
