/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/13 13:55:12 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief This thread waits for a signal from the philo handler.
 *        If the simulation stoped the philo handler is
 *        releasing the semaphore for all philos.
 */
void*	t_mon_sim_state(void *p)
{
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	sem_wait(ph->sem_stop_simulation.sem); //signal from philo_handler (philo has to post philo times on finish)
	set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
	sem_post(ph->sem_print_block.sem);
	return (NULL);
}

/**
 * @brief Check if philo died based on the previous eating time.
 */
static int	philo_died(t_philo_handler *ph, t_philo *philo)
{
	int		ms;
	t_tv	tv_last_meal;
	t_tv	tv_curr;
	// int meals;

	// get_int_sem(&philo->sem_meals, &meals);
	// if (ph->meal_limit && meals >= ph->meals_per_philo)
	// 	return (0);
	get_tv_sem(&philo->sem_tv_last_meal, &tv_last_meal);
	get_current_time(&tv_curr);
	ms = get_time_duration_in_ms(tv_last_meal, tv_curr);
	if (ms >= ph->time_to_die)
	{
		print_philo_state(ph, philo, PHILO_IS_DEAD);
		return (1);
	}
	return (0);
}

/**
 * @brief Thread to monitor each philo death.
 *        Stops also if the simualation is finished.
 */
void*	t_mon_philo_death(void *p)
{
	int sim_state;
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	sim_state = SIM_RUNING;
	while (sim_state == SIM_RUNING)
	{
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (philo_died(ph, philo))
			break;
		usleep(ms_to_us(MS_DEATH_CHECK));
	}
	set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
	return (NULL);
}

