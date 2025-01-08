/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:07:15 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	update_meals_eaten(t_philo *philo)
// {
// 	sem_wait(philo->sem_meals.sem.sem);
// 	philo->sem_meals.value += 1;
// 	sem_post(philo->sem_meals.sem.sem);
// }

// void	update_last_meal_time(t_philo *philo)
// {
// 	sem_wait(philo->sem_tv_last_meal.sem.sem);
// 	get_current_time(&philo->sem_tv_last_meal.tv);
// 	sem_post(philo->sem_tv_last_meal.sem.sem);
// }

// int	philo_usleep(t_philo_handler	*ph, int ms_sleep)
// {
// 	int	ms;
// 	int sim_state;
// 	t_tv tv_start;
// 	t_tv tv_curr;

// 	ms = 0;
// 	sim_state = SIM_RUNING;
// 	get_current_time(&tv_start);
// 	while (ms <= ms_sleep)
// 	{
// 		if (sim_state != SIM_RUNING)
// 			return (SIM_FINISHED);
// 		usleep(ms_to_us(MS_SIM_SLEEP));
// 		get_int_sem(&ph->sem_sim_state, &sim_state);
// 		get_current_time(&tv_curr);
// 		ms = get_time_duration_in_ms(tv_start, tv_curr);
// 	}
// 	return (SIM_RUNING);
// }

// int check_simulation_state(t_philo_handler *ph, t_philo *philo)
// {
// 	int sim_state;
// 	int meals_eaten;

// 	sim_state = 0;
// 	meals_eaten = -1;
// 	if (ph->meal_limit)
// 		get_int_sem(&philo->sem_meals, &meals_eaten);
// 	if (meals_eaten >= ph->meals_per_philo)
// 		return (SIM_FINISHED);
// 	get_int_sem(&ph->sem_sim_state, &sim_state);
// 	return (sim_state);
// }
