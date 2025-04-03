/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_semaphores.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:20:27 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/03 09:03:17 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	close_sem_philo_handler(t_philo_handler *ph)
{
	bool	unlink;

	if (!ph)
		return (SUCCESS);
	unlink = !ph->is_child;
	close_semaphore(&ph->sem_forks_request, unlink);
	close_semaphore(&ph->sem_forks, unlink);
	close_semaphore(&ph->sem_print, unlink);
	close_semaphore(&ph->sem_philo_finished, unlink);
	close_semaphore(&ph->sem_stop_simulation, unlink);
	close_semaphore(&ph->sem_stop_feedback, unlink);
	close_semaphore(&ph->sem_philos_started, unlink);
	close_semaphore(&ph->sem_death, unlink);
	close_semaphore(&ph->sem_error, unlink);
	return (SUCCESS);
}

static int	close_sem_philos(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;
	bool	unlink;

	if (!ph || !ph->philo_lst)
		return (SUCCESS);
	unlink = !ph->is_child;
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		close_semaphore(&philo->sem_time_of_death.sem, unlink);
		close_semaphore(&philo->sem_sim_state.sem, unlink);
		i++;
	}
	return (SUCCESS);
}

int	close_semaphores(t_philo_handler *ph)
{
	if (!ph)
		return (SUCCESS);
	close_sem_philo_handler(ph);
	close_sem_philos(ph);
	return (SUCCESS);
}
