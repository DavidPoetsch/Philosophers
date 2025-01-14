/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/14 10:15:54 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_formated_time(t_philo_handler *ph)
{
	t_tv	tv_curr;
	size_t	ms;

	if (get_current_time(&tv_curr) == ERROR)
		return ;
	ms = get_time_duration_in_ms(ph->tv_start, tv_curr);
	printf("%10zu ", ms);
}

void	print_philo_state(t_philo_handler *ph, int id, int state)
{
	int sim_state;

	sim_state = SIM_FINISHED;
	lock_mutex(&ph->m_print);
	get_int_mutex(&ph->m_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		print_formated_time(ph);
		if (state == PHILO_IS_ALIVE)
			printf("%d is alive.\n", id);
		else if (state == PHILO_HAS_TAKEN_FORK)
			printf("%d has taken a fork.\n", id);
		else if (state == PHILO_IS_EATING)
			printf("%d is eating.\n", id);
		else if (state == PHILO_IS_SLEEPING)
			printf("%d is sleeping.\n", id);
		else if (state == PHILO_IS_THINKING)
			printf("%d is thinking.\n", id);
		else if (state == PHILO_IS_DEAD)
			printf("%d died.\n", id);
	}
	pthread_mutex_unlock(&ph->m_print.m);
}

void	print_philo_state_fork(t_philo_handler *ph, t_philo *philo, int fork)
{
	int sim_state;

	sim_state = SIM_FINISHED;
	lock_mutex(&ph->m_print);
	get_int_mutex(&ph->m_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		print_formated_time(ph);
		if (DEBUG && fork == 1)
			printf("%d has taken fork. 1: (%p)\n", philo->id, philo->fork1);
		else if (DEBUG && fork == 2)
			printf("%d has taken fork. 2: (%p)\n", philo->id, philo->fork2);
		else
			printf("%d has taken a fork.\n", philo->id);
	}
	pthread_mutex_unlock(&ph->m_print.m);
}
