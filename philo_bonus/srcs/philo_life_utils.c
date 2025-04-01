/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 21:12:44 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_time_to_die(t_philo *philo, unsigned long long ttd,
		unsigned long long us_curr)
{
	sem_wait(philo->sem_time_of_death.sem.sem);
	philo->local_time_of_death = (us_curr + ttd);
	philo->sem_time_of_death.value = philo->local_time_of_death;
	sem_post(philo->sem_time_of_death.sem.sem);
}

void	send_finished(t_philo_handler *ph, t_philo *philo)
{
	if (philo->finished)
		return ;
	sem_post(ph->sem_philo_finished.sem);
	philo->finished = true;
}

bool	sim_running(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	if (ph->meal_limit && philo->meals >= ph->meals_per_philo)
		send_finished(ph, philo);
	if (get_curr_us() >= philo->local_time_of_death)
		return (false);
	sim_state = SIM_RUNING;
	get_int_sem(&philo->sem_sim_state, &sim_state);
	return (sim_state == SIM_RUNING);
}

int	philo_usleep(t_philo *philo, unsigned long long us_sleep)
{
	int					i;
	int					sim_state;
	unsigned long long	us_curr;
	unsigned long long	us_end;

	i = 0;
	sim_state = SIM_RUNING;
	us_curr = get_curr_us();
	us_end = us_curr + us_sleep;
	while (us_curr < us_end)
	{
		if (i++ >= 5000)
		{
			get_int_sem(&philo->sem_sim_state, &sim_state);
			i = 0;
		}
		if (sim_state != SIM_RUNING)
			break ;
		usleep(USLEEP_PAUSE);
		us_curr = get_curr_us();
	}
	get_int_sem(&philo->sem_sim_state, &sim_state);
	return (sim_state);
}
