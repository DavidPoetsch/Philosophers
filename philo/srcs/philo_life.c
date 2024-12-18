/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 17:27:29 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void eat(t_philo_handler	*ph, t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork1->lock);
	pthread_mutex_lock(&philo->fork2->lock);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	// usleep(ms_to_us(TIME_TO_TAKE_FORKS)); //! delete
	update_last_meal_time(philo);
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	// philo_usleep(ph, ph->time_to_eat);
	usleep(ms_to_us(ph->time_to_eat));
	pthread_mutex_unlock(&philo->fork2->lock);
	pthread_mutex_unlock(&philo->fork1->lock);
	update_meals_eaten(philo);
}

void go_sleep(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	// philo_usleep(ph, ph->time_to_sleep);
	usleep(ms_to_us(ph->time_to_sleep));
}

void	think(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
}

// todo do lonely philo routine
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
