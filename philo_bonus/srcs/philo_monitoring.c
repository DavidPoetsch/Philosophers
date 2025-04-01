/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 20:48:17 by dpotsch          ###   ########.fr       */
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
	}
}

/**
 * @brief ### Check if philo died based on the previous eating time.
 * 
 * - Block death prints of other
 * 
 * - Wait until every philo posted on sem_stop_feedback
 * 
 * - Print death time.
 */
static bool	philo_died(t_philo_handler *ph, t_philo *philo)
{
	int					sim_state;
	unsigned long long	us_curr;
	unsigned long long	time_of_death;

	sim_state = SIM_FINISHED;
	get_ull_sem(&philo->sem_time_of_death, &time_of_death);
	us_curr = get_curr_us();
	if (us_curr >= time_of_death)
	{
		sem_wait(ph->sem_death.sem);
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (sim_state == SIM_RUNING)
		{
			set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
			if (ph->philos == 1)
				sem_post(ph->sem_forks.sem);
			wait_for_other_philos_to_finish(ph);
			print_philo_dead(ph, philo, us_curr);
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
		usleep(DEATH_CHECK_PAUSE);
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (sim_state == SIM_FINISHED)
			break ;
		if (philo_died(ph, philo))
			break ;
	}
	return (NULL);
}
