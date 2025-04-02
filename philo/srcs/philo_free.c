/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:01:45 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/02 12:45:38 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	destroy_mutexs(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	destroy_mutex(&ph->m_print);
	destroy_mutex(&ph->m_sim_state.m);
	destroy_mutex(&ph->m_error.m);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		destroy_mutex(&philo->own_fork);
		destroy_mutex(&philo->m_meals.m);
		destroy_mutex(&philo->m_time_of_death.m);
		i++;
	}
	return (SUCCESS);
}

int	philo_free(t_philo_handler *ph)
{
	if (!ph)
		return (SUCCESS);
	destroy_mutexs(ph);
	free(ph);
	return (SUCCESS);
}
