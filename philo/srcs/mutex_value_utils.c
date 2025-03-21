/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_value_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:12:20 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/21 11:38:23 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Increment int mutex by 1 with INT_MAX limit.
 *
 * @param t_mut mutex
 * @return int SUCCESS or ERROR
 */
int	inc_int_mutex(t_int_mutex *t_mut)
{
	if (!t_mut)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m.m) != M_LOCK_SUCCESS)
		return (ERROR);
	if (t_mut->value < INT_MAX)
		t_mut->value += 1;
	else
		return (ERROR);
	pthread_mutex_unlock(&t_mut->m.m);
	return (SUCCESS);
}

/**
 * @brief ### Set the int mutex to value.
 *
 * @param t_mut mutex
 * @param value new value
 * @return int SUCCESS or ERROR
 */
int	set_int_mutex(t_int_mutex *t_mut, int value)
{
	if (!t_mut)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m.m) != M_LOCK_SUCCESS)
		return (ERROR);
	t_mut->value = value;
	pthread_mutex_unlock(&t_mut->m.m);
	return (SUCCESS);
}

/**
 * @brief ### Get the value from an t_int_mutex.
 *
 * @param t_mut mutex
 * @param value value pointer
 * @return int SUCCESS or ERROR
 */
int	get_int_mutex(t_int_mutex *t_mut, int *value)
{
	if (!t_mut || !value)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m.m) == M_LOCK_SUCCESS)
	{
		*value = t_mut->value;
		pthread_mutex_unlock(&t_mut->m.m);
		return (SUCCESS);
	}
	return (ERROR);
}

/**
 * @brief ### Set the time value mutex to value
 *
 * @param t_mut mutex
 * @param tv_new new time value
 * @return int SUCCESS or ERROR
 */
int	set_tv_mutex(t_tv_mutex *t_mut, t_tv tv_new)
{
	if (!t_mut)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m.m) == M_LOCK_SUCCESS)
	{
		t_mut->tv.tv_sec = tv_new.tv_sec;
		t_mut->tv.tv_usec = tv_new.tv_usec;
		pthread_mutex_unlock(&t_mut->m.m);
		return (SUCCESS);
	}
	return (ERROR);
}

/**
 * @brief ### Get the value from an t_tv_mutex.
 *
 * @param t_mut mutex
 * @param tv_res timevalue struct pointer (result)
 * @return int SUCCESS or ERROR
 */
int	get_tv_mutex(t_tv_mutex *t_mut, t_tv *tv_res)
{
	if (!t_mut || !tv_res)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m.m) == M_LOCK_SUCCESS)
	{
		tv_res->tv_sec = t_mut->tv.tv_sec;
		tv_res->tv_usec = t_mut->tv.tv_usec;
		pthread_mutex_unlock(&t_mut->m.m);
		return (SUCCESS);
	}
	return (ERROR);
}
