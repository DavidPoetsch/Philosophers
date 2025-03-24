/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/24 16:48:38 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_start_time(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	if (gettimeofday(&ph->tv_start, NULL) != 0)
	{
		ft_puterr(ERR_GETTIMEOFDAY);
		return (ERROR);
	}
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		philo->sem_tv_last_meal.tv.tv_sec = ph->tv_start.tv_sec;
		philo->sem_tv_last_meal.tv.tv_usec = ph->tv_start.tv_usec;
		i++;
	}
	return (SUCCESS);
}

void	calculate_time_to_think(t_philo_handler *ph)
{
	ph->time_to_think = 0;
	if (ph->time_to_sleep < ph->time_to_eat)
	{
		ph->time_to_think = ph->time_to_eat - ph->time_to_sleep;
		ph->time_to_think += MS_DELAY_THINKING;
	}
}
