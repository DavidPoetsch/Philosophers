/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:01:45 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 11:55:51 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_philos(t_philo_handler *ph)
{
	if (!ph || !ph->philo_lst)
		return (SUCCESS);
	free(ph->philo_lst);
	free(ph->forks);
	ph->philo_lst = NULL;
	ph->forks = NULL;
	return (SUCCESS);
}

static int	destroy_mutexs(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	destroy_mutex(&ph->m_print);
	destroy_mutex(&ph->m_sim_state.m);
	destroy_mutex(&ph->m_error.m);
	destroy_mutex(&ph->m_all_philos_finished.m);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		destroy_mutex(&ph->forks[i]);
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
	if (ph->state != PH_STATE_PHILOS_INIT)
		return (SUCCESS);
	destroy_mutexs(ph);
	free_philos(ph);
	return (SUCCESS);
}
