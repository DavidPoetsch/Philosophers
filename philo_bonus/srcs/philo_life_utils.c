/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 09:20:09 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_last_meal_time(t_philo *philo, t_tv *tv)
{
	sem_wait(philo->sem_tv_last_meal.sem.sem);
	if (!tv)
		get_current_time(&philo->sem_tv_last_meal.tv);
	else
	{
		philo->sem_tv_last_meal.tv.tv_sec = tv->tv_sec;
		philo->sem_tv_last_meal.tv.tv_usec = tv->tv_usec;
	}
	sem_post(philo->sem_tv_last_meal.sem.sem);
}

bool	sim_running(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	if (ph->meal_limit && philo->meals >= ph->meals_per_philo)
		send_finished(ph, philo);
	sim_state = SIM_RUNING;
	get_int_sem(&philo->sem_sim_state, &sim_state);
	return (sim_state == SIM_RUNING);
}

int	sim_state_usleep(t_philo *philo, int ms, bool check_now)
{
	static int	ms_curr;
	int			sim_state;

	ms_curr += ms;
	sim_state = SIM_RUNING;
	if (ms_curr >= MS_CHECK_SIM_STATE || check_now)
	{
		get_int_sem(&philo->sem_sim_state, &sim_state);
		ms_curr = 0;
	}
	return (sim_state);
}

int	philo_usleep(t_philo *philo, int ms_sleep)
{
	int		ms;
	int		sim_state;
	t_tv	tv_start;
	t_tv	tv_curr;

	ms = 0;
	sim_state = SIM_RUNING;
	get_current_time(&tv_start);
	while (ms < ms_sleep && sim_state == SIM_RUNING)
	{
		usleep(US_USLEEP_PAUSE);
		get_current_time(&tv_curr);
		ms = get_time_duration_in_ms(tv_start, tv_curr);
		sim_state = sim_state_usleep(philo, ms, false);
	}
	return (sim_state_usleep(philo, 0, true));
}

void	send_finished(t_philo_handler *ph, t_philo *philo)
{
	if (philo->finished)
		return ;
	sem_post(ph->sem_philo_finished.sem);
	philo->finished = true;
}
