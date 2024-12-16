/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/16 16:54:29 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_formated_time(t_philo_handler *ph)
{
	struct timeval	tv_curr;
	long	seconds;
	long	microseconds;
	long	milliseconds;

	if (gettimeofday(&tv_curr, NULL) != 0)
	{
		printf("Time error: ");
		return;
	}
	seconds = tv_curr.tv_sec - ph->tv_start.tv_sec;
	microseconds = ph->tv_start.tv_usec - tv_curr.tv_usec;
	if (microseconds < 0)
		microseconds = -microseconds;
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	printf("%10ld: ", milliseconds);
}

void	print_philo_state(t_philo_handler *ph, int id, int state)
{
	pthread_mutex_lock(&ph->print_lock);
	print_formated_time(ph);
	if (state == PHILO_STATE_UNDEFINED)
		printf("Philo %d state undefined.\n", id);
	else if (state == PHILO_HAS_TAKEN_FORK)
		printf("Philo %d has taken a fork.\n", id);
	else if (state == PHILO_IS_EATING)
		printf("Philo %d is eating.\n", id);
	else if (state == PHILO_IS_SLEEPING)
		printf("Philo %d is sleeping.\n", id);
	else if (state == PHILO_IS_THINKING)
		printf("Philo %d is thinking.\n", id);
	else if (state == PHILO_DIED)
		printf("Philo %d died.\n", id);
	pthread_mutex_unlock(&ph->print_lock);
}
