/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 16:41:35 by dpotsch          ###   ########.fr       */
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

void	update_time_to_die(t_philo *philo, unsigned long long ttd)
{
	lock_mutex(&philo->m_time_of_death.m);
	philo->m_time_of_death.value = get_curr_us() + ttd;
	pthread_mutex_unlock(&philo->m_time_of_death.m.m);
}

int	philo_usleep(t_philo_handler *ph, unsigned long long us_sleep)
{
	int					sim_state;
	unsigned long long	us_end;
	unsigned long long	us_curr;

	sim_state = SIM_RUNING;
	us_curr = 0;
	us_end = get_curr_us() + us_sleep;
	while (us_curr < us_end)
	{
		get_int_mutex(&ph->m_sim_state, &sim_state);
		if (sim_state != SIM_RUNING)
			break ;
		usleep(US_USLEEP_PAUSE);
		us_curr = get_curr_us();
	}
	return (sim_state);
}
