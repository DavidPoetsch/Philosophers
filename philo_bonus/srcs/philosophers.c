/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 20:20:01 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		res = start_error_handler_thread(&ph);
	if (res == SUCCESS)
		res = start_philo_processes(&ph);
	if (res == SUCCESS)
		sim_monitoring(&ph);
	wait_philo_processes(&ph);
	join_error_handler_thread(&ph);
	close_semaphores(&ph);
	philo_free(&ph);
	return (EXIT_SUCCESS);
}
