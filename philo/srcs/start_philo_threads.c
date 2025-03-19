/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:06 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 15:35:08 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static double	get_thread_delay(t_philo_handler *ph)
{
	double	delay;

	delay = 0.0;
	if (ph->philos <= 1 || ph->philos % 2 == 0)
		return (0.0);
	if (ph->time_to_eat < ph->time_to_die)
	{
		delay = ((double)ph->time_to_die) / ((double)ph->philos * 2);
		delay *= 1000;
	}
	return (delay);
}

static void	start_threads_odd_even_philos(t_philo_handler *ph, bool odd)
{
	int		i;
	double	delay;

	delay = get_thread_delay(ph);
	i = 0;
	while (i < ph->philos)
	{
		if (((i % 2 == 0) && !odd) || ((i % 2 != 0) && odd))
		{
			pthread_create(&ph->philo_lst[i].ptid, NULL, philo_life,
				&ph->philo_lst[i]);
			if (delay > 0)
				usleep(delay);
		}
		i++;
	}
}

int	start_philo_threads(t_philo_handler *ph)
{
	int	i;

	i = 0;
	if (ph->philos % 2 != 0)
	{
		start_threads_odd_even_philos(ph, false);
		start_threads_odd_even_philos(ph, true);
		return (SUCCESS);
	}
	i = 0;
	while (i < ph->philos)
	{
		pthread_create(&ph->philo_lst[i].ptid, NULL, philo_life,
			&ph->philo_lst[i]);
		i++;
	}
	return (SUCCESS);
}
