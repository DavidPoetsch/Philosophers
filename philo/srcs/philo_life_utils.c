/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/24 15:49:12 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_meals_eaten(t_philo *philo)
{
	inc_int_mutex(&philo->m_meals);
}

void	update_last_meal_time(t_philo *philo)
{
	lock_mutex(&philo->m_tv_last_meal.m);
	get_current_time(&philo->m_tv_last_meal.tv);
	pthread_mutex_unlock(&philo->m_tv_last_meal.m.m);
}

bool	sim_runing(t_philo_handler *ph)
{
	int	sim_state;

	sim_state = SIM_FINISHED;
	get_int_mutex(&ph->m_sim_state, &sim_state);
	return (sim_state == SIM_RUNING);
}

int	sim_state_usleep(t_philo_handler *ph, int *ms_curr, bool check_now)
{
	int	sim_state;

	sim_state = SIM_RUNING;
	if ((*ms_curr) >= MS_CHECK_SIM_STATE || check_now)
	{
		get_int_mutex(&ph->m_sim_state, &sim_state);
		(*ms_curr) = 0;
	}
	return (sim_state);
}

int	philo_usleep(t_philo_handler *ph, t_philo *philo, int ms_sleep)
{
	int		ms;
	int		ms_curr;
	int		sim_state;
	t_tv	tv_start;
	t_tv	tv_curr;

	(void)philo;
	ms = 0;
	ms_curr = 0;
	sim_state = SIM_RUNING;
	get_current_time(&tv_start);
	while (ms < ms_sleep && sim_state == SIM_RUNING)
	{
		usleep(US_SIM_SLEEP);
		get_current_time(&tv_curr);
		ms = get_time_duration_in_ms(tv_start, tv_curr);
		ms_curr += ms;
		sim_state = sim_state_usleep(ph, &ms_curr, false);
	}
	return (sim_state_usleep(ph, &ms_curr, true));
}
