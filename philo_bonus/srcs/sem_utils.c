/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/07 16:59:50 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_semaphore(sem_t *sem, const char *name, int value)
{
	sem = sem_open(name, O_CREAT, 0644, value);
	if (sem == SEM_FAILED)
	{
		ft_puterr(ERR_SEM_INIT);
		return (ERROR);
	}
	return (SUCCESS);
}

int	set_int_sem(t_int_sem *t_sem, int value)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(&t_sem->sem);
	t_sem->value = value;
	sem_post(&t_sem->sem);
	return (SUCCESS);
}

int	get_int_sem(t_int_sem *t_sem, int *value)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(&t_sem->sem);
	(*value) = t_sem->value;
	sem_post(&t_sem->sem);
	return (SUCCESS);
}

int	set_tv_sem(t_tv_sem *t_sem, t_tv tv_new)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(&t_sem->sem);
	t_sem->tv.tv_sec = tv_new.tv_sec;
	t_sem->tv.tv_usec = tv_new.tv_usec;
	sem_post(&t_sem->sem);
	return (SUCCESS);
}

int	get_tv_sem(t_tv_sem *t_sem, t_tv *tv_res)
{
	if (!t_sem)
		return (ERROR);
	sem_wait(&t_sem->sem);
	tv_res->tv_sec = t_sem->tv.tv_sec;
	tv_res->tv_usec = t_sem->tv.tv_usec;
	sem_post(&t_sem->sem);
	return (SUCCESS);
}
