/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 15:35:08 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_philo_death(t_philo_handler *ph, t_philo *philo,
		t_tv *tv_curr)
{
	int		ms;
	t_tv	tv_last_meal;

	get_tv_mutex(&philo->m_tv_last_meal, &tv_last_meal);
	ms = get_time_duration_in_ms(tv_last_meal, *tv_curr);
	if (ms >= ph->time_to_die)
	{
		print_philo_state(ph, philo->id, PHILO_IS_DEAD);
		return (SIM_FINISHED);
	}
	return (SIM_RUNING);
}

static int	philo_meals_finished(t_philo_handler *ph, t_philo *philo,
		int *philos_finished)
{
	int	meals;

	if (ph->meal_limit == false)
		return (SIM_RUNING);
	meals = 0;
	get_int_mutex(&philo->m_meals, &meals);
	if (meals >= ph->meals_per_philo)
		(*philos_finished)++;
	if (*philos_finished >= ph->philos)
		return (SIM_FINISHED);
	return (SIM_RUNING);
}

static int	check_philos_state(t_philo_handler *ph, t_tv tv_curr)
{
	int		i;
	t_philo	*philo;
	int		sim_state;
	int		philos_finished;

	i = 0;
	philos_finished = 0;
	sim_state = SIM_FINISHED;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		sim_state = philo_meals_finished(ph, philo, &philos_finished);
		if (sim_state != SIM_FINISHED)
			sim_state = check_philo_death(ph, philo, &tv_curr);
		if (sim_state == SIM_FINISHED)
			break ;
		i++;
	}
	return (sim_state);
}

static void	*philo_monitoring(void *p)
{
	int				sim_state;
	t_philo_handler	*ph;
	t_tv			tv_curr;

	if (!p)
		return (NULL);
	ph = (t_philo_handler *)p;
	while (1)
	{
		sim_state = SIM_RUNING;
		if (get_current_time(&tv_curr) == ERROR)
			sim_state = SIM_FINISHED;
		if (sim_state == SIM_RUNING)
			sim_state = check_philos_state(ph, tv_curr);
		if (sim_state == SIM_FINISHED)
		{
			set_state_finished(ph);
			break ;
		}
		usleep(ms_to_us(MS_MON_SLEEP));
	}
	return (NULL);
}

int	start_monitoring_thread(t_philo_handler *ph)
{
	pthread_create(&ph->ptid_mon, NULL, philo_monitoring, ph);
	return (SUCCESS);
}
