/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:08:57 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/19 12:10:27 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	ask_for_eat_permission(t_philo_handler *ph, t_philo *philo)
// {
// 	int	result;

// 	result = EATING_DENIED;
// 	if (pthread_mutex_lock(&ph->eat_lock) != M_LOCK_SUCCESS)
// 		return (result);
// 	ph->last_lock_id = philo->id;
// 	if (ph->sim_state == SIM_FINISHED)
// 		result = EATING_DENIED;
// 	else if (ph->philos == 1)
// 		result = EATING_ALLOWED;
// 	else if (philo->fork1->state == FORK_AVAILABLE
// 		&& philo->fork2->state == FORK_AVAILABLE)
// 	{
// 		philo->fork1->state = FORK_UNAVAILABLE;
// 		philo->fork2->state = FORK_UNAVAILABLE;
// 		result = EATING_ALLOWED;
// 	}
// 	pthread_mutex_unlock(&ph->eat_lock);
// 	return (result);
// }

// int check_simulation_state(t_philo_handler *ph, t_philo *philo)
// {
// 	int sim_state;
// 	int meals_left;

// 	meals_left = 0;
// 	pthread_mutex_lock(&philo->meals_lock);
// 	meals_left = philo_meals_left(ph, philo);
// 	pthread_mutex_unlock(&philo->meals_lock);
// 	if (meals_left <= 0)
// 		return (SIM_FINISHED);
// 	pthread_mutex_lock(&ph->sim_state_lock);
// 	sim_state = ph->sim_state;
// 	pthread_mutex_unlock(&ph->sim_state_lock);
// 	return (sim_state);
// }
