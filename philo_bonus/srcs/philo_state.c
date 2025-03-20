/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/20 16:31:01 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	block_printing(t_philo_handler *ph)
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

static int	print_formated_time(t_philo_handler *ph)
{
	t_tv	tv_curr;
	size_t	ms;

	get_current_time(&tv_curr);
	ms = get_time_duration_in_ms(ph->tv_start, tv_curr);
	ft_putnbr((size_t)ms);
	ft_putstr(" ");
	return (SUCCESS);
}

int	print_state(t_philo_handler *ph, int id, char *str)
{
	int	res;

	res = print_formated_time(ph);
	if (res == SUCCESS)
	{
		ft_putnbr((size_t)id);
		ft_putstr(str);
	}
	return (res);
}

void	print_philo_state(t_philo_handler *ph, t_philo *philo, int state)
{
	int	res;
	int	sim_state;

	sim_state = SIM_FINISHED;
	res = SUCCESS;
	sem_wait(ph->sem_print.sem);
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		if (state == PHILO_IS_ALIVE)
			res = print_state(ph, philo->id, " is alive.\n");
		else if (state == PHILO_HAS_TAKEN_FORK)
			res = print_state(ph, philo->id, " has taken a fork.\n");
		else if (state == PHILO_IS_EATING)
			res = print_state(ph, philo->id, " is eating.\n");
		else if (state == PHILO_IS_SLEEPING)
			res = print_state(ph, philo->id, " is sleeping.\n");
		else if (state == PHILO_IS_THINKING)
			res = print_state(ph, philo->id, " is thinking.\n");
		else if (state == PHILO_IS_DEAD)
			res = print_state(ph, philo->id, " died.\n");
		if (state == PHILO_IS_DEAD || res != SUCCESS)
			block_printing(ph);
	}
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
