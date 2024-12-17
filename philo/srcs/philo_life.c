/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 17:23:46 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void take_forks(t_philo_handler	*ph, t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork1->lock);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	if (ph->philos > 1)
		pthread_mutex_lock(&philo->fork2->lock);
	usleep(ms_to_us(TIME_TO_TAKE_FORKS));
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
}

void eat(t_philo_handler	*ph, t_philo	*philo)
{
	int i;

	if (ph->sim_state == SIM_FINISHED)
		return;
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	i = 0;
	while(i < ph->time_to_eat && ph->sim_state == SIM_RUNING)
	{
		usleep(ms_to_us(1));
		i++;
	}
}

void	put_forks_back(t_philo_handler	*ph, t_philo	*philo)
{
	pthread_mutex_unlock(&philo->fork1->lock);
	if (ph->philos > 1)
		pthread_mutex_unlock(&philo->fork2->lock);
	if (pthread_mutex_lock(&ph->lock) == M_LOCK_SUCCESS)
	{
		philo->fork1->state = FORK_AVAILABLE;
		philo->fork2->state = FORK_AVAILABLE;
	}
	pthread_mutex_unlock(&ph->lock);
}

void go_sleep(t_philo_handler	*ph, t_philo	*philo)
{
	int i;

	if (ph->sim_state == SIM_FINISHED)
		return;
	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	i = 0;
	while(i < ph->time_to_sleep && ph->sim_state == SIM_RUNING)
	{
		usleep(ms_to_us(1));
		i++;
	}
}

void	*philo_life(void *p)
{
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	while(philo->meals < ph->meals_per_philo && ph->sim_state == SIM_RUNING)
	{
		if (ask_for_eat_permission(ph, philo) == EATING_ALLOWED)
		{
			take_forks(ph, philo);
			eat(ph, philo);
			put_forks_back(ph, philo);
			go_sleep(ph, philo);
			if (ph->sim_state == SIM_RUNING)
				print_philo_state(ph, philo->id, PHILO_IS_THINKING);
		}
	}
	return (NULL);
}
