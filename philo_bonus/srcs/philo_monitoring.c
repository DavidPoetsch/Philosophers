/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 12:43:56 by dpotsch          ###   ########.fr       */
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
	sem_post(ph->sem_stop_feedback.sem);
	return (NULL);
}

static void	wait_for_other_philos_to_finish(t_philo_handler *ph)
{
	int	i;

	post_simulation_finished(ph);
	i = ph->philos;
	while (i > 0)
	{
		sem_wait(ph->sem_stop_feedback.sem);
		i--;
		if (i == 0)
			break ;
	}
}

/**
 * @brief Check if philo died based on the previous eating time.
 */
static bool	philo_died(t_philo_handler *ph, t_philo *philo)
{
	int		sim_state;
	int		ms;
	t_tv	tv_last_meal;
	t_tv	tv_curr;

	sim_state = SIM_FINISHED;
	get_tv_sem(&philo->sem_tv_last_meal, &tv_last_meal);
	get_current_time(&tv_curr);
	ms = get_time_duration_in_ms(tv_last_meal, tv_curr);
	if (ms >= ph->time_to_die)
	{
		sem_wait(ph->sem_death.sem);
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (sim_state == SIM_RUNING)
		{
			set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
			if (ph->philos == 1)
				sem_post(ph->sem_forks.sem);
			wait_for_other_philos_to_finish(ph);
			print_philo_state(ph, philo, PHILO_IS_DEAD);
		}
		sem_post(ph->sem_death.sem);
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
	while (1)
	{
		usleep(US_DEATH_CHECK_PAUSE);
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (sim_state == SIM_FINISHED)
			break ;
		if (philo_died(ph, philo))
			break ;
	}
	return (NULL);
}
