/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/14 10:53:24 by dpotsch          ###   ########.fr       */
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

void	print_debug_info(t_philo_handler *ph)
{
	int i;
	t_philo *philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		printf("address of philo %d fork 1: %p\n",i + 1, philo->fork1);
		printf("address of philo %d fork 2: %p\n",i + 1, philo->fork2);
		i++;
	}
}

//! test 181 605 200 200 10
//601 is a very tight timing, and the more philos you have the slower it gets, so with that many it dies... Which is fine imo
//If you increase it to 605 or something it should work though
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
	if (res == ERROR)
		return (EXIT_FAILURE);
	ph.m_sim_state.value = SIM_RUNING;
	start_monitoring_thread(&ph);
	start_philo_threads(&ph);
	join_philo_threads(&ph);
	pthread_join(ph.ptid_mon, NULL);
	//! free stuff / forks/ philos
	philo_free(&ph);
	return (EXIT_SUCCESS);
}
