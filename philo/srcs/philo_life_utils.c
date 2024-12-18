/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 17:17:35 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_lock);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_lock);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_lock);
	if (gettimeofday(&philo->tv_last_meal, NULL) != 0)
	{
		printf("Time error: ");
		return ;
	}
	pthread_mutex_unlock(&philo->meals_lock);
}

int philo_meals_left(t_philo_handler *ph, t_philo *philo)
{
	if (ph->meal_limit == false)
		return (1);
	if (philo->meals < ph->meals_per_philo)
		return (1);
	return (0);
}

void	philo_usleep(t_philo_handler	*ph, int ms_sleep)
{
	int ms_slept;
	int sim_state;

	ms_slept = 0;
	pthread_mutex_lock(&ph->sim_state_lock);
	sim_state = ph->sim_state;
	pthread_mutex_unlock(&ph->sim_state_lock);
	while(ms_slept < ms_sleep && sim_state == SIM_RUNING)
	{
		pthread_mutex_lock(&ph->sim_state_lock);
		sim_state = ph->sim_state;
		pthread_mutex_unlock(&ph->sim_state_lock);
		usleep(ms_to_us(MS_SIM_SLEEP));
		ms_slept += MS_SIM_SLEEP;
	}
}
