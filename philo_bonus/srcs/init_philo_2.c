/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 10:02:06 by dpotsch          ###   ########.fr       */
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
		update_time_to_die(philo, ph->time_to_die, ph->start_time);
		i++;
	}
	return (SUCCESS);
}
