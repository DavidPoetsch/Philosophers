/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/31 12:01:20 by dpotsch          ###   ########.fr       */
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

	ph->start_time = get_curr_us();
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		update_time_to_die(philo, ph->start_time);
		i++;
	}
	return (SUCCESS);
}

void	calculate_time_to_think(t_philo_handler *ph, t_philo *philo)
{
	philo->time_to_think = 0;
	if (ph->philos % 2 != 0)
	{
		philo->time_to_think = US_DELAY_THINKING;
		if (philo->time_to_sleep < philo->time_to_eat)
		{
			philo->time_to_think = philo->time_to_eat - philo->time_to_sleep;
			philo->time_to_think += US_DELAY_THINKING;
		}
	}
}
