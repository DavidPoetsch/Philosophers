/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:37:56 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	set_int_sem(t_int_sem *t_sem, int value)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(t_sem->sem.sem);
	t_sem->value = value;
	sem_post(t_sem->sem.sem);
	return (SUCCESS);
}

int	get_int_sem(t_int_sem *t_sem, int *value)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(t_sem->sem.sem);
	(*value) = t_sem->value;
	sem_post(t_sem->sem.sem);
	return (SUCCESS);
}

int	set_tv_sem(t_tv_sem *t_sem, t_tv tv_new)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(t_sem->sem.sem);
	t_sem->tv.tv_sec = tv_new.tv_sec;
	t_sem->tv.tv_usec = tv_new.tv_usec;
	sem_post(t_sem->sem.sem);
	return (SUCCESS);
}

int	get_tv_sem(t_tv_sem *t_sem, t_tv *tv_res)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(t_sem->sem.sem);
	tv_res->tv_sec = t_sem->tv.tv_sec;
	tv_res->tv_usec = t_sem->tv.tv_usec;
	sem_post(t_sem->sem.sem);
	return (SUCCESS);
}
