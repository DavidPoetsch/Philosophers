/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:51:16 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/13 17:55:21 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	handle_fork_failure(t_philo *philo)
{
	philo->process.state = STATE_PROCESS_FORK_FAILED;
	philo->process.exit_status = EXIT_FAILURE;
	//todo set simulation state to finished
	ft_puterr(ERR_FORK_PROCESS);
}

static double get_process_delay(t_philo_handler *ph)
{
	double delay;

	//! original old version
	// if (ph->time_to_eat > 5 && ph->philos > 1 && ph->philos % 2 != 0)
	// 	delay = ((((double)ph->time_to_eat - 5) / (double)(ph->philos -1)) * 1000);

	delay = 0.0;
	if (ph->philos <= 1 || ph->philos % 2 == 0)
		return (0.0);
	if (ph->time_to_eat < ph->time_to_die)
	{
		delay = ((double)ph->time_to_die) / ((double)ph->philos * 2);
		delay *= 1000;
	}
	return (delay);
}

int	start_philo_process(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;
	double delay;

	delay = get_process_delay(ph);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		philo->process.state = STATE_PROCESS_FORKED;
		philo->process.pid = fork();
		if (philo->process.pid == FAILED)
		{
			handle_fork_failure(philo);
			return (ERROR);
		}
		else if (philo->process.pid == CHILD)
			philo_life(&ph->philo_lst[i]);
		i++;
		usleep(delay);
	}
	return (SUCCESS);
}
