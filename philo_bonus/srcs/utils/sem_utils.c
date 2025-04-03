/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/03 09:24:14 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	init_semaphore(t_sem *sem, char *name, int value)
{
	if (!sem || (!name && !sem->name))
		return (ERROR);
	if (name != NULL)
		sem->name = name;
	sem->state = SEM_STATE_FAILED;
	sem->sem = sem_open(sem->name, O_CREAT | O_EXCL, 0644, value);
	if (sem->sem == SEM_FAILED)
	{
		sem_unlink(sem->name);
		sem->sem = sem_open(sem->name, O_CREAT | O_EXCL, 0644, value);
		if (sem->sem == SEM_FAILED)
		{
			ft_puterr(ERR_SEM_INIT);
			sem_close(sem->sem);
			sem_unlink(sem->name);
			return (ERROR);
		}
	}
	sem->state = SEM_STATE_OPEN;
	return (SUCCESS);
}

static void	print_close_err(char *sem_name, char *err)
{
	ft_puterr("close ");
	ft_puterr(sem_name);
	ft_puterr(": ");
	ft_puterr(err);
}

void	free_sem_name(t_sem *sem)
{
	if (!sem || !sem->name)
		return ;
	if (sem->free_name)
	{
		free(sem->name);
		sem->name = NULL;
	}
}

int	close_semaphore(t_sem *sem, bool unlink)
{
	if (!sem || !sem->name)
		return (ERROR);
	if (sem->state != SEM_STATE_OPEN)
	{
		free_sem_name(sem);
		return (SUCCESS);
	}
	if (sem_close(sem->sem) == FAILED)
		print_close_err(sem->name, ERR_SEM_CLOSE);
	sem->state = SEM_STATE_CLOSED;
	if (unlink && sem_unlink(sem->name) == FAILED)
		print_close_err(sem->name, ERR_SEM_UNLINK);
	sem->state = SEM_STATE_UNLINKED;
	free_sem_name(sem);
	return (SUCCESS);
}
