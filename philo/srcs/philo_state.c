/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 17:21:58 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static inline void	print_state(unsigned long long us_duration, int id,
		char *str)
{
	printf("%llu %d %s\n", us_duration / 1000ULL, id, str);
}

unsigned long long	print_philo_state(t_philo_handler *ph, int id, int state)
{
	unsigned long long	curr_us;
	unsigned long long	us_duration;

	lock_mutex(&ph->m_print);
	curr_us = get_curr_us();
	us_duration = curr_us - ph->start_time;
	if (state == PHILO_IS_ALIVE)
		print_state(us_duration, id, "is alive");
	else if (state == PHILO_IS_EATING)
		print_state(us_duration, id, "is eating");
	else if (state == PHILO_IS_SLEEPING)
		print_state(us_duration, id, "is sleeping");
	else if (state == PHILO_IS_THINKING)
		print_state(us_duration, id, "is thinking");
	else if (state == PHILO_IS_DEAD)
		print_state(us_duration, id, "died");
	pthread_mutex_unlock(&ph->m_print.m);
	return (curr_us);
}

void	print_philo_dead(t_philo_handler *ph, t_philo *philo,
		unsigned long long tod)
{
	unsigned long long	us_duration;

	lock_mutex(&ph->m_print);
	us_duration = tod - ph->start_time;
	print_state(us_duration, philo->id, "died");
	pthread_mutex_unlock(&ph->m_print.m);
}

void	print_philo_state_fork(t_philo_handler *ph, t_philo *philo, int fork)
{
	unsigned long long	curr_us;
	unsigned long long	us_duration;

	lock_mutex(&ph->m_print);
	curr_us = get_curr_us();
	us_duration = curr_us - ph->start_time;
	if (DEBUG)
	{
		printf("%llu ", us_duration / 1000ULL);
		if (fork == 1)
			printf("%d has taken fork 1: (%p)\n", philo->id, &philo->fork1);
		else if (fork == 2)
			printf("%d has taken fork 2: (%p)\n", philo->id, philo->fork2);
	}
	else
		print_state(us_duration, philo->id, "has taken a fork");
	pthread_mutex_unlock(&ph->m_print.m);
}

/**
 * @brief ### Print error
 *
 * - lock print mutex
 *
 * - print error
 *
 * - set simulation state SIM_FINISHED
 *
 * - set error
 *
 * @param ph handler struct.
 * @param msg error message.
 * @param error error code.
 */
void	print_error(t_philo_handler *ph, char *msg, int error)
{
	lock_mutex(&ph->m_print);
	ft_puterr(msg);
	set_int_mutex(&ph->m_error, error);
	set_int_mutex(&ph->m_sim_state, SIM_FINISHED);
	pthread_mutex_unlock(&ph->m_print.m);
}
