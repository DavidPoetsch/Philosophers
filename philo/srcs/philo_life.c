/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/15 09:53:40 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int eat(t_philo_handler	*ph, t_philo	*philo)
{
	int res;

	lock_mutex(philo->fork1);
	print_philo_state_fork(ph, philo, 1);
	lock_mutex(philo->fork2);
	print_philo_state_fork(ph, philo, 2);
	// usleep(ms_to_us(TIME_TO_TAKE_FORKS)); //! delete
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	update_last_meal_time(philo);
	res = philo_usleep(ph, ph->time_to_eat);
	pthread_mutex_unlock(&philo->fork2->m);
	pthread_mutex_unlock(&philo->fork1->m);
	update_meals_eaten(philo);
	return (res);
}

int go_sleep(t_philo_handler	*ph, t_philo	*philo)
{
	int res;

	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	res = philo_usleep(ph, ph->time_to_sleep);
	return (res);
}

/**
 * @brief Delay needed for odd number of philos.
 *        The delay is necessary for fair fork access.
 */
void	think(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	if (ph->philos % 2 != 0)
		usleep(ms_to_us(2));
}

/**
 * @brief Routine for 1 philo.
 * Philo should die because he can only get 1 fork.
 */
void	lonely_philo_life(t_philo_handler *ph, t_philo *philo)
{
	if (ph->philos > 1)
		return;
	lock_mutex(philo->fork1);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	while(1)
	{
		if (check_simulation_state(ph) != SIM_RUNING)
			break;
	}
	pthread_mutex_unlock(&philo->fork1->m);
}

/**
 * @brief Life of a philosopher (EAT-SLEEP-THINK-REPEAT).
 */
void	*philo_life(void *p)
{
	int res;
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	// if (philo->id % 2 == 0)
	// 	usleep(ms_to_us(10));
	lonely_philo_life(ph, philo);
	while(check_simulation_state(ph) == SIM_RUNING)
	{
		res = eat(ph, philo);
		if (res == SIM_RUNING)
			res = go_sleep(ph, philo);
		if (res == SIM_RUNING)
			think(ph, philo);
	}
	return (NULL);
}
