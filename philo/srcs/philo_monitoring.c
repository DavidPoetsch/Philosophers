/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/11 10:13:53 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static inline int	check_philo_death(t_philo_handler *ph, t_philo *philo)
{
	int					all_philos_finished;
	unsigned long long	time_of_death;
	unsigned long long	curr_us;

	all_philos_finished = 0;
	time_of_death = 0;
	get_ull_mutex(&philo->m_time_of_death, &time_of_death);
	curr_us = get_curr_us();
	if (curr_us >= time_of_death)
	{
		set_int_mutex(&ph->m_sim_state, SIM_FINISHED);
		print_philo_dead(ph, philo, curr_us);
		return (SIM_FINISHED);
	}
	return (SIM_RUNING);
}

static inline int	philo_meals_finished(t_philo_handler *ph, t_philo *philo,
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

static inline int	check_philos_state(t_philo_handler *ph)
{
	int	i;
	int	sim_state;
	int	philos_finished;

	philos_finished = 0;
	sim_state = SIM_RUNING;
	i = 0;
	while (i < ph->philos && sim_state == SIM_RUNING)
	{
		sim_state = check_philo_death(ph, &ph->philo_lst[i]);
		i++;
	}
	i = 0;
	while (i < ph->philos && sim_state == SIM_RUNING)
	{
		sim_state = philo_meals_finished(ph, &ph->philo_lst[i],
				&philos_finished);
		i++;
	}
	return (sim_state);
}

bool	general_error(t_philo_handler *ph)
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

	if (!p)
		return (NULL);
	ph = (t_philo_handler *)p;
	sim_state = SIM_RUNING;
	while (sim_state == SIM_RUNING && !general_error(ph))
	{
		sim_state = check_philos_state(ph);
		usleep(MON_PAUSE);
	}
	set_state_finished(ph);
	return (NULL);
}
