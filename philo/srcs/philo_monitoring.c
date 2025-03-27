/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 17:48:55 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_philo_death(t_philo_handler *ph, t_philo *philo,
		t_tv *tv_curr)
{
	size_t		us;
	t_tv	tv_last_meal;

	get_tv_mutex(&philo->m_tv_last_meal, &tv_last_meal);
	us = get_time_duration_in_us(tv_last_meal, *tv_curr);
	if (us >= (size_t)(ph->time_to_die * 1000L))
	{
		set_int_mutex(&ph->m_sim_state, SIM_FINISHED);
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

static bool	general_error(t_philo_handler *ph)
{
	int	error_code;

	error_code = ERROR;
	get_int_mutex(&ph->m_error, &error_code);
	return (error_code != SUCCESS);
}

void	*philo_monitoring(void *p)
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
		if (sim_state == SIM_FINISHED || general_error(ph))
		{
			set_state_finished(ph);
			break ;
		}
		usleep(US_MON_PAUSE);
	}
	return (NULL);
}
