/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:06 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 19:18:10 by dpotsch          ###   ########.fr       */
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
	t_philo	*philo;
	int		res;
	int		i;

	if (!ph)
		return (ERROR);
	i = 0;
	res = SUCCESS;
	while (res == SUCCESS && i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (!condition || condition(philo->id))
			res = t_create(&philo->t_philo, philo_life, philo);
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
	usleep(DELAY_T_CREATE);
	if (res == SUCCESS)
		res = start_philo_threads_conditioned(ph, &is_even);
	return (res);
}
