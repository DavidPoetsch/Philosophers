/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:11:07 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/20 12:05:22 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_debug_info(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		printf("address of philo %d fork 1: %p\n", i + 1, philo->fork1);
		printf("address of philo %d fork 2: %p\n", i + 1, philo->fork2);
		i++;
	}
}

bool	fail_count(int value)
{
	static int i;

	i++;
	if (i == value)
		return (true);
	return (false);
}
