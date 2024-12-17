/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 17:23:32 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_formated_time(t_philo_handler *ph)
{
	t_tv	tv_curr;
	long	ms;

	if (gettimeofday(&tv_curr, NULL) != 0)
	{
		printf("Time error: ");
		return ;
	}
	ms = get_time_duration_in_ms(ph->tv_start, tv_curr);
	printf("%10ld: ", ms);
}

void	print_philo_state(t_philo_handler *ph, int id, int state)
{
	pthread_mutex_lock(&ph->print_lock);
	if (ph->sim_state == SIM_RUNING)
	{
		print_formated_time(ph);
		if (state == PHILO_IS_ALIVE)
			printf("Philo %d is alive.\n", id);
		else if (state == PHILO_HAS_TAKEN_FORK)
			printf("Philo %d has taken a fork.\n", id);
		else if (state == PHILO_IS_EATING)
			printf("Philo %d is eating.\n", id);
		else if (state == PHILO_IS_SLEEPING)
			printf("Philo %d is sleeping.\n", id);
		else if (state == PHILO_IS_THINKING)
			printf("Philo %d is thinking.\n", id);
		else if (state == PHILO_IS_DEAD)
			printf("Philo %d died.\n", id);
	}
	pthread_mutex_unlock(&ph->print_lock);
}
