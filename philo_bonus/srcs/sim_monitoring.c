/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitoring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:28:30 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:08:48 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	post_simulation_finished(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		sem_post(ph->sem_forks.sem);
		sem_post(ph->sem_forks_request.sem);
		sem_post(ph->sem_stop_simulation.sem);
		i++;
	}
	return (SUCCESS);
}

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
