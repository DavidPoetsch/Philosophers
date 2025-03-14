/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:07:24 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_last_meal_time(t_philo *philo)
{
	sem_wait(philo->sem_tv_last_meal.sem.sem);
	get_current_time(&philo->sem_tv_last_meal.tv);
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

int	philo_usleep(t_philo *philo, int ms_sleep)
{
	int		ms;
	int		ms_check;
	int		sim_state;
	t_tv	tv_start;
	t_tv	tv_curr;

	ms = 0;
	ms_check = 0;
	sim_state = SIM_RUNING;
	get_current_time(&tv_start);
	while (ms < ms_sleep && sim_state == SIM_RUNING)
	{
		usleep(US_SIM_SLEEP);
		get_current_time(&tv_curr);
		ms = get_time_duration_in_ms(tv_start, tv_curr);
		ms_check += ms;
		if (ms_check >= MS_CHECK_SIM_STATE)
		{
			get_int_sem(&philo->sem_sim_state, &sim_state);
			ms_check = 0;
		}
	}
	get_int_sem(&philo->sem_sim_state, &sim_state);
	return (sim_state);
}

void	send_finished(t_philo_handler *ph, t_philo *philo)
{
	if (philo->finished)
		return ;
	sem_post(ph->sem_philo_finished.sem);
	philo->finished = true;
}
