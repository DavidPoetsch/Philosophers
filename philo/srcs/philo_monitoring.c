/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 17:30:49 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int check_philo_death(t_philo_handler *ph, t_philo *philo, t_tv	*tv_curr)
{
	long	ms;

	ms = get_time_duration_in_ms(philo->tv_last_meal, *tv_curr);
	if (ms >= ph->time_to_die)
	{
		print_philo_state(ph, philo->id, PHILO_IS_DEAD);
		return (SIM_FINISHED);
	}
	return (SIM_RUNING);
}

static int	check_philos_state(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;
	t_tv	tv_curr;
	int sim_state;
	int philo_meals;

	if (get_current_time(&tv_curr) == ERROR)
		return (SIM_FINISHED);
	i = 0;
	philo_meals = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		pthread_mutex_lock(&philo->meals_lock);
		philo_meals += philo_meals_left(ph, philo);
		sim_state = check_philo_death(ph, philo, &tv_curr);
		pthread_mutex_unlock(&philo->meals_lock);
		if (sim_state == SIM_FINISHED)
			break;
		i++;
	}
	if (philo_meals == 0)
		return (SIM_FINISHED);
	return (sim_state);
}

void	update_sim_state(t_philo_handler *ph, int sim_state)
{
	pthread_mutex_lock(&ph->sim_state_lock);
	ph->sim_state = sim_state;
	pthread_mutex_unlock(&ph->sim_state_lock);
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
		sim_state = check_philos_state(ph);
		if (sim_state == SIM_FINISHED)
		{
			update_sim_state(ph, sim_state);
			break;
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
