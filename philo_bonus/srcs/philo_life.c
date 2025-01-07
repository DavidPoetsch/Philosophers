/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/07 13:03:57 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int eat(t_philo_handler	*ph, t_philo	*philo)
{
	int res;

	pthread_mutex_lock(philo->fork1);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	pthread_mutex_lock(philo->fork2);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	// usleep(ms_to_us(TIME_TO_TAKE_FORKS)); //! delete
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	update_last_meal_time(philo);
	res = philo_usleep(ph, ph->time_to_eat);
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
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

void	think(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	if (ph->philos % 2 != 0)
		usleep(ms_to_us(20));
	//! more accurate calculation needed
	// !delay needed for FAIR thread balance
}

/**
 * @brief Routine for 1 philo.
 * Philo should die because he can only get 1 fork.
 */
void	lonely_philo_life(t_philo_handler *ph, t_philo *philo)
{
	if (ph->philos > 1)
		return;
	pthread_mutex_lock(philo->fork1);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	while(1)
	{
		if (check_simulation_state(ph, philo) != SIM_RUNING)
			break;
	}
}

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
	if (philo->id % 2 == 0)
		usleep(ms_to_us(10));
	lonely_philo_life(ph, philo);
	while(check_simulation_state(ph, philo) == SIM_RUNING)
	{
		res = eat(ph, philo);
		if (res == SIM_RUNING)
			res = go_sleep(ph, philo);
		if (res == SIM_RUNING)
			think(ph, philo);
	}
	return (NULL);
}
