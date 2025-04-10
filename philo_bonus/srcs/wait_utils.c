/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:13:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/02 14:02:32 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	wait_philo_processes(t_philo_handler *ph)
{
	int	i;

	if (!ph || !ph->philo_lst)
		return (SUCCESS);
	i = 0;
	while (i < ph->philos)
	{
		wait_for_process(&ph->philo_lst[i].process);
		i++;
	}
	return (SUCCESS);
}

void	wait_for_process(t_process *process)
{
	if (!process)
		return ;
	if (process->state == STATE_PROCESS_FORKED)
	{
		waitpid(process->pid, &process->exit_status, 0);
		if (WIFEXITED(process->exit_status))
			process->exit_status = WEXITSTATUS(process->exit_status);
		process->state = STATE_PROCESS_FINISHED;
	}
}
