/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 17:20:11 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static inline void	print_state(unsigned long long us_duration, int id,
		char *str)
{
	printf("%llu %d %s\n", us_duration / 1000ULL, id, str);
}

unsigned long long	print_philo_state(t_philo_handler *ph, t_philo *philo,
		int state)
{
	unsigned long long	curr_us;
	unsigned long long	us_duration;

	sem_wait(ph->sem_print.sem);
	curr_us = get_curr_us();
	us_duration = curr_us - ph->start_time;
	if (state == PHILO_IS_ALIVE)
		print_state(us_duration, philo->id, "is alive");
	else if (state == PHILO_HAS_TAKEN_FORK)
		print_state(us_duration, philo->id, "has taken a fork");
	else if (state == PHILO_IS_EATING)
		print_state(us_duration, philo->id, "is eating");
	else if (state == PHILO_IS_SLEEPING)
		print_state(us_duration, philo->id, "is sleeping");
	else if (state == PHILO_IS_THINKING)
		print_state(us_duration, philo->id, "is thinking");
	sem_post(ph->sem_print.sem);
	return (curr_us);
}

void	print_philo_dead(t_philo_handler *ph, t_philo *philo,
		unsigned long long tod)
{
	unsigned long long	us_duration;

	sem_wait(ph->sem_print.sem);
	us_duration = tod - ph->start_time;
	print_state(us_duration, philo->id, "died");
	sem_post(ph->sem_print.sem);
}

void	print_error_msg(t_philo_handler *ph, char *msg, bool post_error)
{
	sem_wait(ph->sem_print.sem);
	if (post_error)
		sem_post(ph->sem_error.sem);
	ft_puterr(msg);
	sem_post(ph->sem_print.sem);
}
