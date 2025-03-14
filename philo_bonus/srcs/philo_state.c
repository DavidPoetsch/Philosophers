/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:35:30 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	print_formated_time(t_philo_handler *ph)
{
	t_tv	tv_curr;
	size_t	ms;

	if (get_current_time(&tv_curr) == ERROR)
		return ;
	ms = get_time_duration_in_ms(ph->tv_start, tv_curr);
	ft_putnbr((size_t)ms);
	ft_putstr(" ");
}

static void	block_printing_after_death(t_philo_handler *ph)
{
	int	i;

	i = ph->philos;
	post_simulation_finished(ph);
	while (i > 0)
	{
		sem_wait(ph->sem_print_block.sem);
		i--;
		if (i == 0)
			break ;
	}
}

void	print_state(int id, char *str)
{
	ft_putnbr((size_t)id);
	ft_putstr(str);
}

void	print_philo_state(t_philo_handler *ph, t_philo *philo, int state)
{
	int	sim_state;

	sim_state = SIM_FINISHED;
	sem_wait(ph->sem_print.sem);
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		print_formated_time(ph);
		if (state == PHILO_IS_ALIVE)
			print_state(philo->id, " is alive.\n");
		else if (state == PHILO_HAS_TAKEN_FORK)
			print_state(philo->id, " has taken a fork.\n");
		else if (state == PHILO_IS_EATING)
			print_state(philo->id, " is eating.\n");
		else if (state == PHILO_IS_SLEEPING)
			print_state(philo->id, " is sleeping.\n");
		else if (state == PHILO_IS_THINKING)
			print_state(philo->id, " is thinking.\n");
		else if (state == PHILO_IS_DEAD)
		{
			print_state(philo->id, " died.\n");
			block_printing_after_death(ph);
		}
	}
	sem_post(ph->sem_print.sem);
}
