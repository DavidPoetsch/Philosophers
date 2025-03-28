/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 13:56:57 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief Initialize start time for all philosophers.
 *
 * @param ph handler struct
 * @return int SUCCESS or ERROR
 */
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
		update_time_to_die(philo, ph->time_to_die);
		i++;
	}
	return (SUCCESS);
}

void	calculate_time_to_think(t_philo_handler *ph)
{
	ph->time_to_think = US_DELAY_THINKING;
	if (ph->time_to_sleep < ph->time_to_eat)
	{
		ph->time_to_think = ph->time_to_eat - ph->time_to_sleep;
		ph->time_to_think += US_DELAY_THINKING;
	}
}
