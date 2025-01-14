/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/14 10:51:05 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <errno.h>

int	lock_mutex(t_mutex *mutex)
{
	int ret;

	if (!mutex)
		return (ERROR);
	ret = pthread_mutex_lock(&mutex->m);
	if (ret != 0) {
			if (ret == EINVAL) {
					fprintf(stderr, "Mutex is not properly initialized\n");
			} else if (ret == EDEADLK) {
					fprintf(stderr, "Deadlock detected\n");
			} else {
					fprintf(stderr, "Unknown error: %d\n", ret);
			}
			return (ERROR);
	}
	return (SUCCESS);
}

int	init_mutex(t_mutex *mutex)
{
	if (!mutex)
		return (ERROR);
	mutex->state = M_STATE_UNDEFINED;
	if (pthread_mutex_init(&mutex->m, NULL) != 0)
	{
		ft_puterr(ERR_MUTEX_INIT);
		return (ERROR);
	}
	mutex->state = M_STATE_INIT;
	return (SUCCESS);
}

int	destroy_mutex(t_mutex *mutex)
{
	if (!mutex)
		return (ERROR);
	if (mutex->state != M_STATE_INIT)
		return (SUCCESS);
	if (pthread_mutex_destroy(&mutex->m) != 0)
	{
		ft_puterr(ERR_MUTEX_DESTROY);
		return (ERROR);
	}
	mutex->state = M_STATE_DESTROYED;
	return (SUCCESS);
}
