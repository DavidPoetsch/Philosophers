/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:06 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 11:07:44 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	start_threads_odd_even_philos(t_philo_handler *ph, bool odd)
{
	int		res;
	int		i;

	i = 0;
	res = SUCCESS;
	while (res == SUCCESS && i < ph->philos)
	{
		if (((i % 2 == 0) && !odd) || ((i % 2 != 0) && odd))
		{
			res = t_create(&ph->philo_lst[i].t_philo, philo_life,
					&ph->philo_lst[i]);
		}
		i++;
	}
	if (res != SUCCESS)
		print_error(ph, ERR_CREATE_THREAD, res);
	return (res);
}

int	start_philo_threads(t_philo_handler *ph)
{
	int	res;
	int	i;

	i = 0;
	res = SUCCESS;
	if (ph->philos % 2 != 0)
	{
		res = start_threads_odd_even_philos(ph, false);
		if (res == SUCCESS)
			res = start_threads_odd_even_philos(ph, true);
	}
	else
	{
		while (res == SUCCESS && i < ph->philos)
		{
			res = t_create(&ph->philo_lst[i].t_philo, philo_life,
					&ph->philo_lst[i]);
			i++;
		}
		if (res != SUCCESS)
			print_error(ph, ERR_CREATE_THREAD, res);
	}
	return (res);
}
