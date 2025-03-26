/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 11:38:49 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	put_forks_down(t_philo *philo)
{
	if (philo->fork_state == PHILO_TOOK_FORK2)
	{
		pthread_mutex_unlock(&philo->fork2->m);
		pthread_mutex_unlock(&philo->fork1->m);
	}
	if (philo->fork_state == PHILO_TOOK_FORK1)
		pthread_mutex_unlock(&philo->fork1->m);
	philo->fork_state = PHILO_HAS_NO_FORKS;
}

void	update_last_meal_time(t_philo *philo)
{
	lock_mutex(&philo->m_tv_last_meal.m);
	get_current_time(&philo->m_tv_last_meal.tv);
	pthread_mutex_unlock(&philo->m_tv_last_meal.m.m);
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

int	philo_usleep(t_philo_handler *ph, int ms_sleep)
{
	int		ms;
	int		ms_curr;
	int		sim_state;
	t_tv	tv_start;
	t_tv	tv_curr;

	ms = 0;
	ms_curr = 0;
	sim_state = SIM_RUNING;
	get_current_time(&tv_start);
	while (ms < ms_sleep && sim_state == SIM_RUNING)
	{
		usleep(US_USLEEP_PAUSE);
		get_current_time(&tv_curr);
		ms = get_time_duration_in_ms(tv_start, tv_curr);
		ms_curr += ms;
		sim_state = sim_state_usleep(ph, &ms_curr, false);
	}
	return (sim_state_usleep(ph, &ms_curr, true));
}
