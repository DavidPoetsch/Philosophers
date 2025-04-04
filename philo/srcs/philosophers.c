/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/04 09:37:31 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ## Philosophers with mutexes.
 *
 * Usage: `./philo [PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP]`
 *
 * Optional: `[number_of_times_each_philosopher_must_eat]`
 */
int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_handler	*ph;
	int				res;

	init_args(&args, argc, argv);
	ph = NULL;
	res = init_philos(args, &ph);
	if (res == SUCCESS)
		res = start_monitoring_thread(ph);
	if (res == SUCCESS)
		res = start_philo_threads(ph);
	join_philo_threads(ph);
	philo_free(ph);
	if (res != SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
