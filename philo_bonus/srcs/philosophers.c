/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/10 08:58:58 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	fork_philo_process(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;

	i = 0;
	while (i < ph->philos)
	{
		if (i == ph->philos -1 && ph->philos % 2 == 0)
			usleep(20);
		philo = &ph->philo_lst[i];
		philo->process.state = STATE_PROCESS_FORKED;
		philo->process.pid = fork();
		if (philo->process.pid < 0)
		{
			philo->process.state = STATE_PROCESS_FORK_FAILED;
			philo->process.exit_status = EXIT_FAILURE;
			//todo set simulation state to finished
			ft_puterr(ERR_FORK_PROCESS);
			return (ERROR);
		}
		else if (philo->process.pid == 0)
			philo_life(&ph->philo_lst[i]);
		i++;
	}
	return (SUCCESS);
}

int	wait_philo_process(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		wait_for_process(&ph->philo_lst[i].process);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_handler	ph;
	int				res;

	memset(&ph, 0, sizeof(t_philo_handler));
	init_args(&args, argc, argv);
	res = init_philos(args, &ph);
	if (res == ERROR)
	{
		//todo close semaphores
		//todo free semaphore names
		close_semaphores(&ph);
		return (EXIT_FAILURE);
	}
	res = start_sim_mon_thread(&ph);
	if (res == SUCCESS)
		fork_philo_process(&ph);
	wait_philo_process(&ph);
	pthread_join(ph.ptid_sim_mon, NULL);
	close_semaphores(&ph);
	return (EXIT_SUCCESS);
}

