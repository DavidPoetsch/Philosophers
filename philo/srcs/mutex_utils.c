/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/19 13:39:59 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(pthread_mutex_t *mt)
{
	if (pthread_mutex_init(mt, NULL) != 0)
	{
		ft_puterr(ERR_MUTEX_INIT);
		return (ERROR);
	}
	return (SUCCESS);
}

int	set_int_mutex(t_int_mutex *t_mut, int value)
{
	if (!t_mut)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m) == M_LOCK_SUCCESS)
	{
		t_mut->value = value;
		pthread_mutex_unlock(&t_mut->m);
		return (SUCCESS);
	}
	return (ERROR);
}

int	get_int_mutex(t_int_mutex *t_mut, int *value)
{
	if (!t_mut || !value)
	{
		return (ERROR);
	}
	if (pthread_mutex_lock(&t_mut->m) == M_LOCK_SUCCESS)
	{
		*value = t_mut->value;
		pthread_mutex_unlock(&t_mut->m);
		return (SUCCESS);
	}
	return (ERROR);
}

int	set_tv_mutex(t_tv_mutex *t_mut, t_tv tv_new)
{
	if (!t_mut)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m) == M_LOCK_SUCCESS)
	{
		t_mut->tv.tv_sec = tv_new.tv_sec;
		t_mut->tv.tv_usec = tv_new.tv_usec;
		pthread_mutex_unlock(&t_mut->m);
		return (SUCCESS);
	}
	return (ERROR);
}

int	get_tv_mutex(t_tv_mutex *t_mut, t_tv *tv_res)
{
	if (!t_mut || !tv_res)
		return (ERROR);
	if (pthread_mutex_lock(&t_mut->m) == M_LOCK_SUCCESS)
	{
		tv_res->tv_sec = t_mut->tv.tv_sec;
		tv_res->tv_usec = t_mut->tv.tv_usec;
		pthread_mutex_unlock(&t_mut->m);
		return (SUCCESS);
	}
	return (ERROR);
}
