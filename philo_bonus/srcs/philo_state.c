/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 14:11:05 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_state(t_philo_handler *ph, int id, char *str,
		unsigned long long *curr_us)
{
	*curr_us = get_curr_us();
	printf("%llu %d %s", (*curr_us) / 1000ULL, id, str);
}

unsigned long long	print_philo_state(t_philo_handler *ph, t_philo *philo,
		int state)
{
	unsigned long long	curr_us;

	sem_wait(ph->sem_print.sem);
	curr_us = 0;
	if (state == PHILO_IS_ALIVE)
		print_state(ph, philo->id, " is alive\n", &curr_us);
	else if (state == PHILO_HAS_TAKEN_FORK)
		print_state(ph, philo->id, " has taken a fork\n", &curr_us);
	else if (state == PHILO_IS_EATING)
		print_state(ph, philo->id, " is eating\n", &curr_us);
	else if (state == PHILO_IS_SLEEPING)
		print_state(ph, philo->id, " is sleeping\n", &curr_us);
	else if (state == PHILO_IS_THINKING)
		print_state(ph, philo->id, " is thinking\n", &curr_us);
	else if (state == PHILO_IS_DEAD)
		print_state(ph, philo->id, " died\n", &curr_us);
	sem_post(ph->sem_print.sem);
	return (curr_us);
}

void	print_error_msg(t_philo_handler *ph, char *msg, bool post_error)
{
	sem_wait(ph->sem_print.sem);
	if (post_error)
		sem_post(ph->sem_error.sem);
	ft_puterr(msg);
	sem_post(ph->sem_print.sem);
}
