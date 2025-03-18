/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/18 11:50:52 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *t_philo_error_handler(void *ptr)
{
	int	i;
	t_philo_handler *ph;

	if (!ptr)
		return (NULL);
	ph = (t_philo_handler *)ptr;
	sem_wait(ph->sem_error.sem);
	post_simulation_finished(ph);
	i = 0;
	while (i < ph->philos)
	{
		sem_post(ph->sem_philo_finished.sem);
		i++;
	}
	return (NULL);
}

/**
 * @brief ## Philosophers with semaphores.
 *
 * Usage: `./philo [PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP]`
 *
 * Optional: `[number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	int				res;
	t_args			args;
	t_philo_handler	ph;

	memset(&ph, 0, sizeof(t_philo_handler));
	init_args(&args, argc, argv);
	res = init_philos(args, &ph);
	if (res == SUCCESS)
		res = t_create(&ph.t_error_handler, t_philo_error_handler, &ph);
	if (res == SUCCESS)
		res = start_philo_processes(&ph);
	if (res == SUCCESS)
		sim_monitoring(&ph);
	if (ph.t_error_handler.state == STATE_THREAD_CREATED)
	{
		sem_post(ph.sem_error.sem);
		t_join(&ph.t_error_handler);
	}
	wait_philo_processes(&ph);
	close_semaphores(&ph);
	philo_free(&ph);
	return (EXIT_SUCCESS);
}
