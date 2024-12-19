/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/19 15:47:28 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_philo_threads(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		pthread_create(&ph->philo_lst[i].ptid, NULL, philo_life,
			&ph->philo_lst[i]);
		i++;
	}
	return (SUCCESS);
}

int	join_philo_threads(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		pthread_join(ph->philo_lst[i].ptid, NULL);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_handler	ph;
	int				res;

	memset(&ph, 0, sizeof(t_philo_handler));
	init_args(&args, argc, argv);
	res = init_philos(args, &ph);
	if (res == ERROR)
		return (EXIT_FAILURE);
	ph.m_sim_state.value = SIM_RUNING;
	start_monitoring_thread(&ph);
	start_philo_threads(&ph);
	join_philo_threads(&ph);
	pthread_join(ph.ptid_mon, NULL);
	return (EXIT_SUCCESS);
}
