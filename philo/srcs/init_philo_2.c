/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:07:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/21 11:24:10 by dpotsch          ###   ########.fr       */
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
		philo->m_tv_last_meal.tv.tv_sec = ph->tv_start.tv_sec;
		philo->m_tv_last_meal.tv.tv_usec = ph->tv_start.tv_usec;
		i++;
	}
	return (SUCCESS);
}
