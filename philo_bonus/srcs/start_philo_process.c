/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:51:16 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/24 17:00:25 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	fork_philo_processes(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		philo->process.state = STATE_PROCESS_FORKED;
		philo->process.pid = fork();
		if (philo->process.pid == FAILED)
		{
			philo->process.state = STATE_PROCESS_FORK_FAILED;
			philo->process.exit_status = EXIT_FAILURE;
			print_error_msg(ph, ERR_FORK_PROCESS, false);
			return (ERROR);
		}
		else if (philo->process.pid == CHILD)
			start_philo_life(ph, philo);
		kill(philo->process.pid, SIGSTOP);
		i++;
	}
	return (SUCCESS);
}

static void	continue_processes(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (philo->process.state == STATE_PROCESS_FORKED)
			kill(philo->process.pid, SIGCONT);
		i++;
	}
}

int	start_philo_processes(t_philo_handler *ph)
{
	int	res;

	res = fork_philo_processes(ph);
	continue_processes(ph);
	if (res != SUCCESS)
	{
		sem_post(ph->sem_philos_started.sem);
		sem_post(ph->sem_error.sem);
	}
	return (res);
}
