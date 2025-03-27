/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 17:34:10 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	put_forks_down(t_philo *philo)
{
	if (philo->fork_state == PHILO_TOOK_FORK2)
	{
		pthread_mutex_unlock(&philo->fork2->m);
		pthread_mutex_unlock(&philo->fork1->m);
	}
	if (philo->fork_state == PHILO_TOOK_FORK1)
		pthread_mutex_unlock(&philo->fork1->m);
	philo->fork_state = PHILO_HAS_NO_FORKS;
}

void	update_last_meal_time(t_philo *philo)
{
	lock_mutex(&philo->m_tv_last_meal.m);
	get_current_time(&philo->m_tv_last_meal.tv);
	pthread_mutex_unlock(&philo->m_tv_last_meal.m.m);
}

int	philo_usleep(t_philo_handler *ph, int ms_sleep)
{
	size_t		us;
	size_t		us_sleep;
	int		sim_state;
	t_tv	tv_start;
	t_tv	tv_curr;

	us = 0;
	us_sleep = ms_sleep * 1000;
	sim_state = SIM_RUNING;
	gettimeofday(&tv_start, NULL);
	while (us < us_sleep)
	{
		get_int_mutex(&ph->m_sim_state, &sim_state);
		if (sim_state != SIM_RUNING)
			break;
		usleep(US_USLEEP_PAUSE);
		gettimeofday(&tv_curr, NULL);
		us = get_time_duration_in_us(tv_start, tv_curr);
	}
	return (sim_state);
}
