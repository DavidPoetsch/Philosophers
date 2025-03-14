/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_semaphores.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:20:27 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 20:29:01 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	close_sem_philo_handler(t_philo_handler *ph)
{
	bool unlink;

	unlink = !ph->is_child;
	close_semaphore(&ph->sem_forks, unlink);
	close_semaphore(&ph->sem_forks_request, unlink);
	close_semaphore(&ph->sem_print, unlink);
	close_semaphore(&ph->sem_print_block, unlink);
	close_semaphore(&ph->sem_philo_finished, unlink);
	close_semaphore(&ph->sem_stop_simulation, unlink);
	return (SUCCESS);
}

static int	close_sem_philos(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;
	bool unlink;

	unlink = !ph->is_child;
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		close_semaphore(&philo->sem_tv_last_meal.sem, unlink);
		close_semaphore(&philo->sem_sim_state.sem, unlink);
		i++;
	}
	return (SUCCESS);
}

int	close_semaphores(t_philo_handler *ph)
{
	close_sem_philo_handler(ph);
	close_sem_philos(ph);
	return (SUCCESS);
}
