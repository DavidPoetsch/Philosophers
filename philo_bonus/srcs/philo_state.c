/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:09:41 by dpotsch          ###   ########.fr       */
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
	sem_wait(ph->sem_print.sem);
	// get_int_sem(&ph->sem_sim_state, &sim_state); //todo fix somehow
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
	sem_post(ph->sem_print.sem);
}
