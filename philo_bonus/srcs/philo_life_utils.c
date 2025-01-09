/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/09 20:25:42 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_meals_eaten(t_philo *philo)
{
	sem_wait(philo->sem_meals.sem.sem);
	philo->sem_meals.value += 1;
	sem_post(philo->sem_meals.sem.sem);
}

void	update_last_meal_time(t_philo *philo)
{
	sem_wait(philo->sem_tv_last_meal.sem.sem);
	get_current_time(&philo->sem_tv_last_meal.tv);
	sem_post(philo->sem_tv_last_meal.sem.sem);
}

int	philo_usleep(t_philo	*philo, int ms_sleep)
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
		get_int_sem(&philo->sem_sim_state, &sim_state);
		get_current_time(&tv_curr);
		ms = get_time_duration_in_ms(tv_start, tv_curr);
	}
	return (SIM_RUNING);
}

