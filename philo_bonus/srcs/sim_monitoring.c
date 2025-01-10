/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitoring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:28:30 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/10 10:04:00 by dpotsch          ###   ########.fr       */
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
		sem_post(ph->sem_stop_simulation.sem);
		i++;
	}
	return (SUCCESS);
}

static void	*t_sim_monitoring(void *p)
{
	int				philo_finished_count;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	ph = (t_philo_handler *)p;
	philo_finished_count = 0;
	while (1)
	{
		sem_wait(ph->sem_philo_finished.sem);
		philo_finished_count++;
		if (philo_finished_count >= ph->philos)
			break ;
	}
	post_simulation_finished(ph);
	// printf("SIM FINISHED\n"); //! delete
	return (NULL);
}

int	start_sim_mon_thread(t_philo_handler *ph)
{
	int	res;

	res = SUCCESS;
	if (pthread_create(&ph->ptid_sim_mon, NULL, t_sim_monitoring, ph) != 0)
		res = ERROR;
	if (res == ERROR)
	{
		ft_puterr(ERR_CREATE_THREAD);
		post_simulation_finished(ph);
	}
	return (SUCCESS);
}
