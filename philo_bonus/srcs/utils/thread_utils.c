/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:26:03 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 19:59:44 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Create thread
 * 
 * @param thread_info thread info struct
 * @param start_routine start routine
 * @param arg argument pointer
 * @return int returns SUCCESS or ERROR
 */
int	t_create(t_thread_info *thread_info, void *(*start_routine)(void *),
		void *arg)
{
	int	res;

	res = pthread_create(&thread_info->ptid, NULL, start_routine, arg);
	if (res != 0)
	{
		thread_info->state = STATE_THREAD_FAILED_TO_CREATE;
		return (ERROR);
	}
	thread_info->state = STATE_THREAD_CREATED;
	return (SUCCESS);
}

/**
 * @brief ### Join thread
 * 
 * - Checks if state == STATE_THREAD_CREATED
 * 
 * @param thread_info thread info struct
 */
void	t_join(t_thread_info *thread_info)
{
	if (!thread_info || thread_info->state != STATE_THREAD_CREATED)
		return ;
	pthread_join(thread_info->ptid, NULL);
	thread_info->state = STATE_THREAD_JOINED;
}
