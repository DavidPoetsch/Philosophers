/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:43:25 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/20 11:49:25 by dpotsch          ###   ########.fr       */
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

int	start_monitoring_thread(t_philo_handler *ph)
{
	int res;

	res = t_create(&ph->t_mon, philo_monitoring, ph);
	if (res != SUCCESS)
		print_error(ph, ERR_CREATE_THREAD, res);
	return (res);
}
