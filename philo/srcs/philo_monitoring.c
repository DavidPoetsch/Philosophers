/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 17:13:17 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_simulation_state(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		if (ph->philo_lst[i].meals < ph->meals_per_philo)
		{
			return (SIM_RUNING);
		}
		i++;
	}
	return (SIM_FINISHED);
}

static int	check_philos_state(t_philo_handler *ph)
{
	t_philo	*philo;
	t_tv	tv_curr;
	long	ms;
	int		i;

	if (gettimeofday(&tv_curr, NULL) != 0)
	{
		printf("Time error: "); // TODO do error
		return (PHILO_IS_DEAD);
	}
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		ms = get_time_duration_in_ms(philo->tv_last_meal, tv_curr);
		if (ms >= ph->time_to_die)
		{
			print_philo_state(ph, philo->id, PHILO_IS_DEAD);
			return (SIM_FINISHED);
		}
		i++;
	}
	return (SIM_RUNING);
}

void	*philo_monitoring(void *p)
{
	int				sim_state;
	t_philo_handler	*ph;

	if (!p)
		return NULL;
	ph = (t_philo_handler *)p;
	while (1)
	{
		sim_state = SIM_RUNING;
		if (pthread_mutex_lock(&ph->lock) != M_LOCK_SUCCESS)
			return NULL;
		if (sim_state != SIM_FINISHED)
			sim_state = check_simulation_state(ph);
		if (sim_state != SIM_FINISHED)
			sim_state = check_philos_state(ph);
		pthread_mutex_unlock(&ph->lock);
		if (sim_state == SIM_FINISHED)
		{
			ph->sim_state = SIM_FINISHED;
			break ;
		}
		usleep(ms_to_us(5));
	}
	return NULL;
}

int	start_monitoring_thread(t_philo_handler *ph)
{
	pthread_create(&ph->ptid_mon, NULL, philo_monitoring, ph);
	return (SUCCESS);
}
