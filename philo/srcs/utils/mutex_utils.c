/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 14:14:18 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/**
 * @brief ### Lock mutex
 *
 * - Lock a mutex of type t_mutex
 * @param mutex
 * @return int
 */
int	lock_mutex(t_mutex *mutex)
{
	int	res;

	if (!mutex)
		return (ERROR);
	res = pthread_mutex_lock(&mutex->m);
	if (res != 0)
	{
		return (res);
	}
	return (SUCCESS);
}

/**
 * @brief ### Initialize mutex
 *
 * sets state to one of these:
 *
 * - M_STATE_INIT
 *
 * - M_STATE_UNDEFINED
 * @param mutex
 * @return int SUCCESS or ERROR
 */
int	init_mutex(t_mutex *mutex)
{
	int	res;

	if (!mutex)
		return (ERROR);
	mutex->state = M_STATE_UNDEFINED;
	res = pthread_mutex_init(&mutex->m, NULL);
	if (res != 0)
	{
		ft_puterr(ERR_MUTEX_INIT);
		return (res);
	}
	mutex->state = M_STATE_INIT;
	return (SUCCESS);
}

/**
 * @brief ### Destroy mutex
 *
 * - destroy mutex and set state to M_STATE_DESTROYED
 *
 * @param mutex
 * @return int
 */
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
