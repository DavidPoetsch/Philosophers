/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:47:44 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 19:57:53 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/**
 * @brief ### Set the value from int semaphore struct
 *
 * @param t_sem semaphore struct
 * @param value new value
 */
void	set_int_sem(t_int_sem *t_sem, int value)
{
	sem_wait(t_sem->sem.sem);
	t_sem->value = value;
	sem_post(t_sem->sem.sem);
}

/**
 * @brief ### Get value from int semaphore
 *
 * @param t_sem semaphore struct
 * @param value value result
 */
void	get_int_sem(t_int_sem *t_sem, int *value)
{
	sem_wait(t_sem->sem.sem);
	(*value) = t_sem->value;
	sem_post(t_sem->sem.sem);
}

/**
 * @brief ### Set the value from ull semaphore struct
 *
 * @param t_sem semaphore struct
 * @param value new value
 */
void	set_ull_sem(t_ull_sem *t_sem, unsigned long long value)
{
	sem_wait(t_sem->sem.sem);
	t_sem->value = value;
	sem_post(t_sem->sem.sem);
}

/**
 * @brief ### Get value from ull semaphore
 *
 * @param t_sem semaphore struct
 * @param value value result
 */
void	get_ull_sem(t_ull_sem *t_sem, unsigned long long *value)
{
	sem_wait(t_sem->sem.sem);
	(*value) = t_sem->value;
	sem_post(t_sem->sem.sem);
}
