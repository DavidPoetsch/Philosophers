/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 15:57:28 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Eat
 *
 * - Take fork 1.
 *
 * - Take fork 2.
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
static int	eat(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	lock_mutex(philo->fork1);
	print_philo_state_fork(ph, philo, 1);
	lock_mutex(philo->fork2);
	print_philo_state_fork(ph, philo, 2);
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	update_last_meal_time(philo);
	sim_state = philo_usleep(philo, ph->time_to_eat);
	pthread_mutex_unlock(&philo->fork2->m);
	pthread_mutex_unlock(&philo->fork1->m);
	update_meals_eaten(philo);
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
static int	go_sleep(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
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
static void	think(t_philo_handler *ph, t_philo *philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	if (ph->philos % 2 != 0)
		usleep(US_DELAY_THINKING);
}

/**
 * @brief ### Routine for 1 philo.
 *
 * - Philo should die because he can only get 1 fork.
 */
static void	lonely_philo_life(t_philo_handler *ph, t_philo *philo)
{
	if (ph->philos > 1)
		return ;
	lock_mutex(philo->fork1);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	while (sim_runing(ph))
	{
		(void)ph;
	}
	pthread_mutex_unlock(&philo->fork1->m);
}

/**
 * @brief ### Life of a philosopher (EAT - SLEEP - THINK - REPEAT).
 */
void	*philo_life(void *p)
{
	int				sim_state;
	t_philo			*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	if (philo->id % 2 == 0 && ph->philos % 2 == 0)
		usleep(ms_to_us(10));
	lonely_philo_life(ph, philo);
	while (sim_runing(ph))
	{
		sim_state = eat(ph, philo);
		if (sim_state == SIM_RUNING)
			sim_state = go_sleep(ph, philo);
		if (sim_state == SIM_RUNING)
			think(ph, philo);
	}
	return (NULL);
}
