/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitoring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:28:30 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 20:25:56 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Post simulation finished
 * 
 * Philos wait on the semaphore sem_stop_simulation.
 * 
 * When the simulation should stop this function is used to signal
 * the philos to stop.
 * 
 * @param ph philo handler struct.
 * @return int SUCCESS.
 */
int	post_simulation_finished(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		sem_post(ph->sem_stop_simulation.sem);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief ### Simulation monitoring.
 * 
 * This function is waiting until every philosopher has finished.
 * 
 * Every philosopher needs to post the semaphore sem_philo_finished.
 * 
 * @param ph philo handler struct
 */
void	sim_monitoring(t_philo_handler *ph)
{
	int				philo_finished_count;

	philo_finished_count = 0;
	while (1)
	{
		sem_wait(ph->sem_philo_finished.sem);
		philo_finished_count++;
		if (philo_finished_count >= ph->philos)
			break ;
	}
	post_simulation_finished(ph);
}
