/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:26:03 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/18 11:40:43 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	t_create(t_thread_info *thread_info, void *(*start_routine)(void *),
		void *arg)
{
	int	ret;

	ret = pthread_create(&thread_info->ptid, NULL, start_routine, arg);
	if (ret != 0)
	{
		ft_puterr(ERR_CREATE_THREAD);
		thread_info->state = STATE_THREAD_FAILED_TO_CREATE;
		return (ERROR);
	}
	thread_info->state = STATE_THREAD_CREATED;
	return (SUCCESS);
}

void	t_join(t_thread_info *thread_info)
{
	if (!thread_info || thread_info->state != STATE_THREAD_CREATED)
		return ;
	pthread_join(thread_info->ptid, NULL);
	thread_info->state = STATE_THREAD_JOINED;
}
