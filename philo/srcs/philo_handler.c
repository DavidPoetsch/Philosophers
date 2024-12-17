/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:08:57 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 16:58:55 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ask_for_eat_permission(t_philo_handler *ph, t_philo *philo)
{
	int	result;

	result = EATING_DENIED;
	if (pthread_mutex_lock(&ph->lock) != M_LOCK_SUCCESS)
		return (result);
	ph->last_lock_id = philo->id;
	if (ph->sim_state == SIM_FINISHED)
		result = EATING_DENIED;
	else if (ph->philos == 1)
		result = EATING_ALLOWED;
	else if (philo->fork1->state == FORK_AVAILABLE
		&& philo->fork2->state == FORK_AVAILABLE)
	{
		philo->fork1->state = FORK_UNAVAILABLE;
		philo->fork2->state = FORK_UNAVAILABLE;
		result = EATING_ALLOWED;
		update_philo_meal_stat(philo);
	}
	pthread_mutex_unlock(&ph->lock);
	return (result);
}
