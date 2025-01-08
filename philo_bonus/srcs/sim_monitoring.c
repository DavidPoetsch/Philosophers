/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitoring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:28:30 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:10:39 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	notify_philos(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		sem_post(ph->sem_sim_state.sem);
		i++;
	}
	return (SUCCESS);
}

static void	*sim_monitoring(void *p)
{
	int				philo_finished_count;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	ph = (t_philo_handler *)p;
	philo_finished_count = 0;
	while (1)
	{
		sem_wait(ph->sem_sim_state.sem);
		philo_finished_count++;
		if (philo_finished_count >= ph->philos)
			break ;
	}
	notify_philos(ph);
	printf("SIM FINISHED\n"); //! delete
	return (NULL);
}

int	start_sim_mon_thread(t_philo_handler *ph)
{
	pthread_create(&ph->ptid_sim_mon, NULL, sim_monitoring, ph);
	return (SUCCESS);
}
