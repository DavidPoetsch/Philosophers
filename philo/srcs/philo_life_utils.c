/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/20 12:10:52 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_meals_eaten(t_philo_handler *ph, t_philo *philo)
{
	int	res;

	res = inc_int_mutex(&philo->m_meals);
	if (res != SUCCESS)
		print_error(ph, ERR_MUTEX_LOCK, res);
}

void	update_last_meal_time(t_philo_handler *ph, t_philo *philo)
{
	int	res;

	res = lock_mutex(&philo->m_tv_last_meal.m);
	if (res == SUCCESS)
	{
		get_current_time(&philo->m_tv_last_meal.tv);
		pthread_mutex_unlock(&philo->m_tv_last_meal.m.m);
	}
	else
		print_error(ph, ERR_MUTEX_LOCK, res);
}

bool	sim_runing(t_philo_handler *ph)
{
	int	res;
	int	sim_state;

	sim_state = SIM_FINISHED;
	res = get_int_mutex(&ph->m_sim_state, &sim_state);
	if (res != SUCCESS)
	{
		print_error(ph, ERR_MUTEX_LOCK, res);
		return (false);
	}
	return (sim_state == SIM_RUNING);
}

int	sim_state_usleep(t_philo_handler *ph, t_philo *philo, int *ms_curr,
		bool check_now)
{
	int	res;
	int	sim_state;

	sim_state = SIM_RUNING;
	if ((*ms_curr) >= MS_CHECK_SIM_STATE || check_now)
	{
		res = get_int_mutex(&philo->m_state, &sim_state);
		if (res != SUCCESS)
			print_error(ph, ERR_MUTEX_LOCK, res);
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
		sim_state = sim_state_usleep(ph, philo, &ms_curr, false);
	}
	return (sim_state_usleep(ph, philo, &ms_curr, true));
}
