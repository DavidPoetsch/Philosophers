/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:43:25 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 15:35:08 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_state_finished(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	set_int_mutex(&ph->m_sim_state, SIM_FINISHED);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		set_int_mutex(&philo->m_state, SIM_FINISHED);
		i++;
	}
}
