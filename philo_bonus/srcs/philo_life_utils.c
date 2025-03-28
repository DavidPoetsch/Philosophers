/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:12:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 14:14:02 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_time_to_die(t_philo *philo, unsigned long long ttd)
{
	sem_wait(philo->sem_tv_last_meal.sem.sem);
	philo->sem_tv_last_meal.value = get_curr_us() + ttd;
	sem_post(philo->sem_tv_last_meal.sem.sem);
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
	sim_state = SIM_RUNING;
	get_int_sem(&philo->sem_sim_state, &sim_state);
	return (sim_state == SIM_RUNING);
}

int	philo_usleep(t_philo *philo, unsigned long long us_sleep)
{
	int					sim_state;
	unsigned long long	us_end;
	unsigned long long	us_curr;

	sim_state = SIM_RUNING;
	us_curr = 0;
	us_end = get_curr_us() + us_sleep;
	while (us_curr < us_end)
	{
		get_int_mutex(&philo->sem_sim_state, &sim_state);
		if (sim_state != SIM_RUNING)
			break ;
		usleep(US_USLEEP_PAUSE);
		us_curr = get_curr_us();
	}
	return (sim_state);
}
