/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:35:24 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/03 09:43:38 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Starting philo life threads
 *
 * - start thread simulation state monitoring.
 *
 * - start thread death monitoring.
 *
 * - start philo life routine.
 */
void	start_philo_threads(t_philo_handler *ph, t_philo *philo)
{
	int				res;
	t_ptr_wrapper	wrapper;

	ph->is_child = true;
	wrapper = void_ptr_wrapper(ph, philo);
	res = t_create(&philo->t_mon_philo_state, t_mon_philo_state, &wrapper);
	if (res == SUCCESS)
		res = t_create(&philo->t_mon_death, t_mon_philo_death, &wrapper);
	if (res == SUCCESS)
		t_philo_life(&wrapper);
	if (res != SUCCESS)
		print_error_msg(ph, ERR_CREATE_THREAD, true);
	if (philo->id == ph->philos)
		sem_post(ph->sem_philos_started.sem);
	if (philo->t_mon_philo_state.state == STATE_THREAD_CREATED)
		t_join(&philo->t_mon_philo_state);
	if (philo->t_mon_death.state == STATE_THREAD_CREATED)
		t_join(&philo->t_mon_death);
	philo_exit(ph, res);
}
