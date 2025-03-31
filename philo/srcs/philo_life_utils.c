/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/31 16:24:57 by dpotsch          ###   ########.fr       */
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

void	update_time_to_die(t_philo *philo, unsigned long long us_curr)
{
	lock_mutex(&philo->m_time_of_death.m);
	if (us_curr == 0)
		us_curr = get_curr_us();
	philo->local_time_of_death = (us_curr + philo->time_to_die) / 1000ULL;
	philo->m_time_of_death.value = philo->local_time_of_death;
	pthread_mutex_unlock(&philo->m_time_of_death.m.m);
}

bool sim_running(t_philo_handler *ph, t_philo *philo)
{
	int sim_state;

	if (get_curr_us() / 1000ULL >= philo->local_time_of_death)
		return (false);
	get_int_mutex(&ph->m_sim_state, &sim_state);
	return (sim_state == SIM_RUNING);
}

int	philo_usleep(t_philo_handler *ph, unsigned long long us_sleep)
{
	int i;
	int					sim_state;
	unsigned long long	us_end;
	unsigned long long	us_curr;

	sim_state = SIM_RUNING;
	us_curr = 0;
	us_end = get_curr_us() + us_sleep;
	while (us_curr < us_end)
	{
		if (i++ >= 10000)
		{
			get_int_mutex(&ph->m_sim_state, &sim_state);
			i = 0;
		}
		if (sim_state != SIM_RUNING)
			break ;
		usleep(US_USLEEP_PAUSE);
		us_curr = get_curr_us();
	}
	get_int_mutex(&ph->m_sim_state, &sim_state);
	return (sim_state);
}
