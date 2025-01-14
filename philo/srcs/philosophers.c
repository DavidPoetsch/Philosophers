/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/14 18:04:56 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

double get_thread_delay(t_philo_handler *ph)
{
	double delay;

	delay = 0.0;
	if (ph->philos <= 1 || ph->philos % 2 == 0)
		return (0.0);
	if (ph->time_to_eat < ph->time_to_die)
	{
		delay = ((double)ph->time_to_die - 10) / ((double)ph->philos - 1);
		delay *= 1000;
	}
	return (delay);
}

void	start_threads_odd_philos(t_philo_handler *ph, bool odd)
{
	int	i;
	double delay;

	delay = get_thread_delay(ph);
	i = 0;
	while (i < ph->philos)
	{
		if (((i % 2 == 0) && !odd) || ((i % 2 != 0) && odd))
		{
			pthread_create(&ph->philo_lst[i].ptid, NULL, philo_life,
				&ph->philo_lst[i]);
			if (delay > 0)
				usleep(delay);
		}
		i++;
	}
}

int	start_philo_threads(t_philo_handler *ph)
{
	int i;

	if (ph->philos % 2 != 0)
	{
		start_threads_odd_philos(ph, false);
		start_threads_odd_philos(ph, true);
		return (SUCCESS);
	}
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
	ph.m_sim_state.value = SIM_RUNING;
	start_monitoring_thread(&ph);
	start_philo_threads(&ph);
	join_philo_threads(&ph);
	pthread_join(ph.ptid_mon, NULL);
	//! free stuff / forks/ philos
	philo_free(&ph);
	return (EXIT_SUCCESS);
}
