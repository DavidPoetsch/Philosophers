/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:06 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/31 16:26:42 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	is_even(int nr)
{
	return (nr % 2 == 0);
}

bool	is_odd(int nr)
{
	return (nr % 2 != 0);
}

static int	start_philo_threads_conditioned(t_philo_handler *ph,
		bool (*condition)(int))
{
	int	res;
	int	i;

	if (!ph)
		return (ERROR);
	i = 0;
	res = SUCCESS;
	while (res == SUCCESS && i < ph->philos)
	{
		if (!condition || condition(i + 1))
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

	res = start_philo_threads_conditioned(ph, &is_odd);
	usleep(2000);
	if (res == SUCCESS)
		res = start_philo_threads_conditioned(ph, &is_even);
	return (res);
}
