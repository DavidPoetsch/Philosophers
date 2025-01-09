/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/09 10:47:19 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_meals.m);
	philo->m_meals.value += 1;
	pthread_mutex_unlock(&philo->m_meals.m);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_tv_last_meal.m);
	get_current_time(&philo->m_tv_last_meal.tv);
	pthread_mutex_unlock(&philo->m_tv_last_meal.m);
}

// void	philo_usleep(t_philo_handler	*ph, int ms_sleep)
// {
// 	int ms_slept;
// 	int sim_state;

// 	ms_slept = 0;
// 	sim_state = 0;
// 	while(sim_state == SIM_RUNING)
// 	{
// 		usleep(ms_to_us(MS_SIM_SLEEP));
// 		ms_slept += MS_SIM_SLEEP;
// 		if (ms_slept >= ms_sleep)
// 			return ;
// 		get_int_mutex(&ph->m_sim_state, &sim_state);
// 	}
// }

int	philo_usleep(t_philo_handler	*ph, int ms_sleep)
{
	int	ms;
	int sim_state;
	t_tv tv_start;
	t_tv tv_curr;

	ms = 0;
	sim_state = SIM_RUNING;
	get_current_time(&tv_start);
	while (ms <= ms_sleep)
	{
		if (sim_state != SIM_RUNING)
			return (SIM_FINISHED);
		usleep(ms_to_us(MS_SIM_SLEEP));
		get_int_mutex(&ph->m_sim_state, &sim_state);
		get_current_time(&tv_curr);
		ms = get_time_duration_in_ms(tv_start, tv_curr);
	}
	return (SIM_RUNING);
}

int check_simulation_state(t_philo_handler *ph, t_philo *philo)
{
	int sim_state;
	int meals_eaten;

	sim_state = 0;
	meals_eaten = -1;
	if (ph->meal_limit)
		get_int_mutex(&philo->m_meals, &meals_eaten);
	if (meals_eaten >= ph->meals_per_philo)
		return (SIM_FINISHED);
	get_int_mutex(&ph->m_sim_state, &sim_state);
	return (sim_state);
}
