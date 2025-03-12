/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/12 21:02:18 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//! test 181 605 200 200 10
//601 is a very tight timing, and the more philos you have the slower it gets, so with that many it dies... Which is fine imo
//If you increase it to 605 or something it should work though

/**
 * @brief ## Philosophers
 * 
 * Usage: `./philo 5 800 200 200`
 * 
 * Args: `number_of_philosophers, time_to_die, time_to_eat, time_to_sleep`
 * 
 * Optional arg: `number_of_times_each_philosopher_must_eat`
 */
int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_handler	ph;
	int				res;

	memset(&ph, 0, sizeof(t_philo_handler));
	init_args(&args, argc, argv);
	res = init_philos(args, &ph);
	if (res == ERROR)
	{
		philo_free(&ph);
		return (EXIT_FAILURE);
	}
	ph.m_sim_state.value = SIM_RUNING;
	start_monitoring_thread(&ph);
	start_philo_threads(&ph);
	join_philo_threads(&ph);
	pthread_join(ph.ptid_mon, NULL);
	philo_free(&ph);
	return (EXIT_SUCCESS);
}
