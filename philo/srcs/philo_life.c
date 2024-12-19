/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/19 16:03:08 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philo_handler	*ph, t_philo	*philo)
{
	pthread_mutex_lock(philo->fork1);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	pthread_mutex_lock(philo->fork2);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	// usleep(ms_to_us(TIME_TO_TAKE_FORKS)); //! delete
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	update_last_meal_time(philo); //! maybe put update also in thread
	philo_usleep(ph, ph->time_to_eat);
	// usleep(ms_to_us(ph->time_to_eat));
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
	update_meals_eaten(philo);
}

void go_sleep(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	philo_usleep(ph, ph->time_to_sleep);
	// usleep(ms_to_us(ph->time_to_sleep));
}

void	think(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	// usleep(ms_to_us(50)); 
	//! more accurate calculation needed
	// !delay needed for FAIR thread balance
}

//! todo do lonely philo routine
//! philo should die because he can only get 1 fork
// void	lonely_philo_life(t_philo_handler *ph, t_philo *philo)
// {
// }

void	*philo_life(void *p)
{
	t_philo	*philo;
	t_philo_handler	*ph;

	//! wait for all threads, reset time
	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	think(ph, philo);
	while(check_simulation_state(ph, philo) == SIM_RUNING)
	{
		eat(ph, philo);
		go_sleep(ph, philo);
		think(ph, philo);
	}
	return (NULL);
}
