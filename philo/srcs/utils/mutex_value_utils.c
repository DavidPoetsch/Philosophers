/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_value_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:12:20 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/04 12:05:49 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/**
 * @brief ### Increment int mutex by 1 with INT_MAX limit.
 *
 * @param t_mut mutex
 * @return int SUCCESS or ERROR
 */
int	inc_int_mutex(t_int_mutex *t_mut)
{
	int	res;

	res = SUCCESS;
	if (!t_mut)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m.m) != M_LOCK_SUCCESS)
		return (ERROR);
	if (t_mut->value < INT_MAX)
		t_mut->value += 1;
	else
		res = ERROR;
	pthread_mutex_unlock(&t_mut->m.m);
	return (res);
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
 * @brief ### Set the ull mutex to value.
 *
 * @param t_mut mutex
 * @param value new value
 * @return int SUCCESS or ERROR
 */
int	set_ull_mutex(t_ull_mutex *t_mut, unsigned long long value)
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
 * @brief ### Get the value from an t_ull_mutex.
 *
 * @param t_mut mutex
 * @param value value pointer
 * @return int SUCCESS or ERROR
 */
int	get_ull_mutex(t_ull_mutex *t_mut, unsigned long long *value)
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
