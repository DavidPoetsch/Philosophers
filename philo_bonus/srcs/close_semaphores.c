/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_semaphores.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:20:27 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:33:05 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	close_sem_philo_handler(t_philo_handler *ph)
{
	close_semaphore(&ph->sem_forks);
	close_semaphore(&ph->sem_print);
	close_semaphore(&ph->sem_print_block);
	close_semaphore(&ph->sem_philo_finished);
	close_semaphore(&ph->sem_stop_simulation);
	return (SUCCESS);
}

static int	close_sem_philos(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		close_semaphore(&philo->sem_tv_last_meal.sem);
		close_semaphore(&philo->sem_sim_state.sem);
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
