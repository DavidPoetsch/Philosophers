/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:13:22 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 12:18:03 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
