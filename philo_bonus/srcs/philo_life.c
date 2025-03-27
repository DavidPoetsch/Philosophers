/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 09:43:15 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Take forks
 *
 * - get fork request semaphore
 *
 * - take two forks
 *
 * - the forks should be evenly shared as semaphores should follow FIFO order.
 *
 * @param ph philo handler struct
 * @param philo philo struct
 * @return int simulation state
 */
int	take_forks(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	sim_state = SIM_FINISHED;
	sem_wait(ph->sem_forks_request.sem);
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		sem_wait(ph->sem_forks.sem);
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (sim_state == SIM_RUNING)
			print_philo_state(ph, philo, PHILO_HAS_TAKEN_FORK);
	}
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		sem_wait(ph->sem_forks.sem);
		get_int_sem(&philo->sem_sim_state, &sim_state);
		if (sim_state == SIM_RUNING)
			print_philo_state(ph, philo, PHILO_HAS_TAKEN_FORK);
	}
	sem_post(ph->sem_forks_request.sem);
	return (sim_state);
}

/**
 * @brief ### Eat
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
	t_tv	tv;
	int		sim_state;

	memset(&tv, 0, sizeof(tv));
	sim_state = SIM_FINISHED;
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		tv = print_philo_state(ph, philo, PHILO_IS_EATING);
		update_last_meal_time(philo, &tv);
		sim_state = philo_usleep(philo, ph->time_to_eat);
	}
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
 * - for the bonus with sempahores we do not need a think time as
 *   semaphores should follow FIFO order at the next fork request.
 *
 * @param ph
 * @param philo
 */
void	think(t_philo_handler *ph, t_philo *philo)
{
	print_philo_state(ph, philo, PHILO_IS_THINKING);
}

/**
 * @brief ### Life of a philosopher (EAT - SLEEP - THINK - REPEAT).
 */
void	*t_philo_life(void *p)
{
	int				sim_state;
	t_philo_handler	*ph;
	t_philo			*philo;

	if (!p)
		return (NULL);
	ph = ((t_ptr_wrapper *)p)->ptr_ph;
	philo = ((t_ptr_wrapper *)p)->ptr_philo;
	philo->finished = false;
	update_last_meal_time(philo, NULL);
	print_philo_state(ph, philo, PHILO_IS_THINKING);
	while (sim_running(ph, philo))
	{
		sim_state = take_forks(ph, philo);
		if (sim_state == SIM_RUNING)
			sim_state = eat(ph, philo);
		put_forks_down(ph);
		if (sim_state == SIM_RUNING)
			sim_state = go_sleep(ph, philo);
		if (sim_state == SIM_RUNING)
			think(ph, philo);
	}
	send_finished(ph, philo);
	return (NULL);
}
