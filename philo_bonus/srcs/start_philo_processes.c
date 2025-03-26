/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_processes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:51:16 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 12:36:57 by dpotsch          ###   ########.fr       */
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
			start_philo_threads(ph, philo);
		kill(philo->process.pid, SIGSTOP);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief ### Continue processes
 * 
 * All processes are stop right after forking.
 * 
 * When all of the are created send signal to continue.
 * 
 * @param ph 
 */
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

/**
 * @brief ### Start all philo processes
 * 
 * @param ph 
 * @return int 
 */
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
