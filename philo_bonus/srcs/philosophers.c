/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/13 18:02:51 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		//todo close semaphores
		//todo free semaphore names
		close_semaphores(&ph);
		return (EXIT_FAILURE);
	}
	res = start_sim_mon_thread(&ph);
	if (res == SUCCESS)
		start_philo_process(&ph);
	wait_philo_processes(&ph);
	pthread_join(ph.ptid_sim_mon, NULL);
	close_semaphores(&ph);
	return (EXIT_SUCCESS);
}
