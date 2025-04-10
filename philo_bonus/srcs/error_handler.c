/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:13:30 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/02 09:01:47 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	unlock_waiting_semaphores(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		sem_post(ph->sem_philo_finished.sem);
		sem_post(ph->sem_stop_feedback.sem);
		i++;
	}
}

void	*t_philo_error_handler(void *ptr)
{
	t_philo_handler	*ph;

	if (!ptr)
		return (NULL);
	ph = (t_philo_handler *)ptr;
	sem_wait(ph->sem_philos_started.sem);
	sem_wait(ph->sem_error.sem);
	post_simulation_finished(ph);
	unlock_waiting_semaphores(ph);
	return (NULL);
}

int	start_error_handler_thread(t_philo_handler *ph)
{
	int	res;

	res = t_create(&ph->t_error_handler, t_philo_error_handler, ph);
	if (res != SUCCESS)
	{
		print_error_msg(ph, ERR_CREATE_THREAD, true);
		post_simulation_finished(ph);
		unlock_waiting_semaphores(ph);
	}
	return (res);
}

void	join_error_handler_thread(t_philo_handler *ph)
{
	if (ph->t_error_handler.state == STATE_THREAD_CREATED)
	{
		sem_post(ph->sem_philos_started.sem);
		sem_post(ph->sem_error.sem);
		t_join(&ph->t_error_handler);
	}
}
