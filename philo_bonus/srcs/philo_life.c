/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/18 11:52:45 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Eat
 *
 * - Get fork access.
 *
 * - Take 2 forks.
 *
 * - update last meal time.
 *
 * - eat for x time.
 *
 * - put forks down.
 *
 * - update meal count.
 *
 * @param ph philo handler
 * @param philo philo
 * @return int sim state
 */
int	eat(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	sem_wait(ph->sem_forks_request.sem);
	sem_wait(ph->sem_forks.sem);
	print_philo_state(ph, philo, PHILO_HAS_TAKEN_FORK);
	sem_wait(ph->sem_forks.sem);
	print_philo_state(ph, philo, PHILO_HAS_TAKEN_FORK);
	sem_post(ph->sem_forks_request.sem);
	print_philo_state(ph, philo, PHILO_IS_EATING);
	update_last_meal_time(philo);
	sim_state = philo_usleep(philo, ph->time_to_eat);
	sem_post(ph->sem_forks.sem);
	sem_post(ph->sem_forks.sem);
	philo->meals++;
	return (sim_state);
}

/**
 * @brief ### Sleep
 *
 * - After eat philo sleeps for x time.
 *
 * @param ph philo handler
 * @param philo philo
 * @return int sim state
 */
int	go_sleep(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	print_philo_state(ph, philo, PHILO_IS_SLEEPING);
	sim_state = philo_usleep(philo, ph->time_to_sleep);
	return (sim_state);
}

/**
 * @brief ### Think
 *
 * - After sleep, philo is thinking.
 *
 * Delay needed for odd number of philos.
 * The delay is necessary for fair fork access.
 *
 * @param ph
 * @param philo
 */
void	think(t_philo_handler *ph, t_philo *philo)
{
	print_philo_state(ph, philo, PHILO_IS_THINKING);
	if (ph->philos % 2 != 0)
		usleep(US_DELAY_THINKING);
}

/**
 * @brief ### Life of a philosopher (EAT - SLEEP - THINK - REPEAT).
 */
static void	*t_philo_life(void *p)
{
	int				sim_state;
	t_philo_handler	*ph;
	t_philo			*philo;

	if (!p)
		return (NULL);
	ph = ((t_ptr_wrapper *)p)->ptr_ph;
	philo = ((t_ptr_wrapper *)p)->ptr_philo;
	philo->finished = false;
	update_last_meal_time(philo);
	print_philo_state(ph, philo, PHILO_IS_THINKING);
	while (sim_running(ph, philo))
	{
		sim_state = eat(ph, philo);
		if (sim_state == SIM_RUNING)
			sim_state = go_sleep(ph, philo);
		if (sim_state == SIM_RUNING)
			think(ph, philo);
	}
	send_finished(ph, philo);
	return (NULL);
}

/**
 * @brief ### Starting philo life process
 *
 * - start thread simulation state monitoring.
 *
 * - start thread death monitoring.
 *
 * - start thread philo life routine.
 */
void	start_philo_life(t_philo_handler *ph, t_philo *philo)
{
	int				res;
	t_ptr_wrapper	wrapper;

	ph->is_child = true;
	wrapper = void_ptr_wrapper(ph, philo);
	res = t_create(&philo->t_mon_philo_state, t_mon_philo_state, &wrapper);
	if (res == SUCCESS)
		res = t_create(&philo->t_mon_death, t_mon_philo_death, &wrapper);
	if (res == SUCCESS)
		res = t_create(&philo->t_philo_life, t_philo_life, &wrapper);
	if (res != SUCCESS)
		sem_post(ph->sem_error.sem);
	if (philo->t_mon_philo_state.state == STATE_THREAD_CREATED)
		t_join(&philo->t_mon_philo_state);
	if (philo->t_mon_death.state == STATE_THREAD_CREATED)
		t_join(&philo->t_mon_death);
	if (philo->t_philo_life.state == STATE_THREAD_CREATED)
		t_join(&philo->t_philo_life);
	close_semaphores(ph);
	philo_free(ph);
	exit(res);
}
