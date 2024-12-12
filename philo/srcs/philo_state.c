/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/12 16:49:55 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
# include "time_utils.h"

void	print_formated_time()
{
	t_time t;

	t = get_timestamp();

	printf("%d %0.2d %0.2d, ", t.year, t.month, t.day);
	printf("%0.2d:%0.2d:%0.2d:%0.2d: ", t.h, t.m, t.s, t.millis);
}

void	print_philo_state(int id, int state)
{
	print_formated_time();
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
}
