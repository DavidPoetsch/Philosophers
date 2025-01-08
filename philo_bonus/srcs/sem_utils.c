/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 14:52:55 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_semaphore(t_sem *sem, int value)
{
	if (!sem || !sem->name)
		return (ERROR);
	sem->state = SEM_STATE_FAILED;
	sem->sem = sem_open(sem->name, O_CREAT, 0644, value);
	if (sem->sem == SEM_FAILED)
	{
		ft_puterr(ERR_SEM_INIT);
		return (ERROR);
	}
	sem->state = SEM_STATE_OPEN;
	return (SUCCESS);
}

int close_semaphore(t_sem *sem)
{
	if (!sem || !sem->name)
		return (ERROR);
	if (sem->state != SEM_STATE_OPEN)
		return (SUCCESS);
	if (sem_close(sem->sem) == -1) {
		ft_puterr(ERR_SEM_CLOSE);
		return (ERROR);
	}
	sem->state = SEM_STATE_CLOSED;
	if (sem_unlink(sem->name) == -1) {
		ft_puterr(ERR_SEM_UNLINK);
		return (ERROR);
	}
	sem->state = SEM_STATE_UNLINKED;
	if (sem->free_name)
	{
		free(sem->name);
		sem->name = NULL;
	}
	return (SUCCESS);
}

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
