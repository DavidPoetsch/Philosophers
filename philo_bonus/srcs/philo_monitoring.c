/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 14:28:36 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief This thread waits for a signal from the philo handler.
 *        If the simulation stoped the philo handler is
 *        releasing the semaphore for all philos.
 */
void	*t_mon_philo_state(void *p)
{
	t_philo_handler	*ph;
	t_philo			*philo;

	if (!p)
		return (NULL);
	ph = ((t_ptr_wrapper *)p)->ptr_ph;
	philo = ((t_ptr_wrapper *)p)->ptr_philo;
	sem_wait(ph->sem_stop_simulation.sem);
	set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
	sem_post(ph->sem_print_block.sem);
	return (NULL);
}

/**
 * @brief Check if philo died based on the previous eating time.
 */
static bool	philo_died(t_philo_handler *ph, t_philo *philo)
{
	int		res;
	int		ms;
	t_tv	tv_last_meal;
	t_tv	tv_curr;

	get_tv_sem(&philo->sem_tv_last_meal, &tv_last_meal);
	res = get_current_time(&tv_curr);
	if (res != SUCCESS)
	{
		print_error_msg(ph, ERR_GETTIMEOFDAY, true);
		return (false);
	}
	ms = get_time_duration_in_ms(tv_last_meal, tv_curr);
	if (ms >= ph->time_to_die)
	{
		print_philo_state(ph, philo, PHILO_IS_DEAD);
		return (true);
	}
	return (false);
}

/**
 * @brief Thread to monitor each philo death.
 *        Stops also if the simualation is finished.
 */
void	*t_mon_philo_death(void *p)
{
	int				sim_state;
	t_philo_handler	*ph;
	t_philo			*philo;

	if (!p)
		return (NULL);
	ph = ((t_ptr_wrapper *)p)->ptr_ph;
	philo = ((t_ptr_wrapper *)p)->ptr_philo;
	sim_state = SIM_RUNING;
	while (sim_state == SIM_RUNING)
	{
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (philo_died(ph, philo))
			break ;
		usleep(ms_to_us(MS_DEATH_CHECK));
	}
	set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
	return (NULL);
}
