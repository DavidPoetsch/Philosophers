/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 10:02:09 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	set_int_sem(t_int_sem *t_sem, int value)
{
	sem_wait(t_sem->sem.sem);
	t_sem->value = value;
	sem_post(t_sem->sem.sem);
}

void	get_int_sem(t_int_sem *t_sem, int *value)
{
	sem_wait(t_sem->sem.sem);
	(*value) = t_sem->value;
	sem_post(t_sem->sem.sem);
}

void	set_ull_sem(t_ull_sem *t_sem, unsigned long long value)
{
	sem_wait(t_sem->sem.sem);
	t_sem->value = value;
	sem_post(t_sem->sem.sem);
}

void	get_ull_sem(t_ull_sem *t_sem, unsigned long long *value)
{
	sem_wait(t_sem->sem.sem);
	(*value) = t_sem->value;
	sem_post(t_sem->sem.sem);
}
