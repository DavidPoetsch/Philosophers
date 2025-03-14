/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:51:16 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:31:52 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static double	get_process_delay(t_philo_handler *ph)
{
	double	delay;

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
			ft_puterr(ERR_FORK_PROCESS);
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
	double	delay;

	delay = get_process_delay(ph);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (philo->process.state == STATE_PROCESS_FORKED)
			kill(philo->process.pid, SIGCONT);
		i++;
		usleep(delay);
	}
}

static void	kill_processes(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (philo->process.state == STATE_PROCESS_FORKED)
			kill(philo->process.pid, SIGKILL);
		i++;
	}
}

int	start_philo_processes(t_philo_handler *ph)
{
	int	res;

	res = fork_philo_processes(ph);
	if (res == SUCCESS)
		continue_processes(ph);
	else
		kill_processes(ph);
	return (res);
}
