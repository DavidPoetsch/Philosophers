/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:10:54 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 09:43:12 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// static void	block_printing(t_philo_handler *ph)
// {
// 	int	i;

// 	i = ph->philos;
// 	post_simulation_finished(ph);
// 	while (i > 0)
// 	{
// 		sem_wait(ph->sem_print_block.sem);
// 		i--;
// 		if (i == 0)
// 			break ;
// 	}
// }

static int	print_formated_time(t_philo_handler *ph, t_tv *tv)
{
	size_t	ms;

	if (!tv)
		return (ERROR);
	if (get_current_time(tv) == ERROR)
	{
		ft_puterr(ERR_GETTIMEOFDAY);
		sem_post(ph->sem_error.sem);
		return (ERROR);
	}
	ms = get_time_duration_in_ms(ph->tv_start, *tv);
	ft_putnbr((size_t)ms);
	ft_putstr(" ");
	return (SUCCESS);
}

int	print_state(t_philo_handler *ph, int id, char *str, t_tv *tv)
{
	int	res;

	res = print_formated_time(ph, tv);
	if (res == SUCCESS)
	{
		ft_putnbr((size_t)id);
		ft_putstr(str);
	}
	return (res);
}

t_tv	print_philo_state(t_philo_handler *ph, t_philo *philo, int state)
{
	t_tv	tv;

	sem_wait(ph->sem_print.sem);
	memset(&tv, 0, sizeof(t_tv));
	if (state == PHILO_IS_ALIVE)
		print_state(ph, philo->id, " is alive.\n", &tv);
	else if (state == PHILO_HAS_TAKEN_FORK)
		print_state(ph, philo->id, " has taken a fork.\n", &tv);
	else if (state == PHILO_IS_EATING)
		print_state(ph, philo->id, " is eating.\n", &tv);
	else if (state == PHILO_IS_SLEEPING)
		print_state(ph, philo->id, " is sleeping.\n", &tv);
	else if (state == PHILO_IS_THINKING)
		print_state(ph, philo->id, " is thinking.\n", &tv);
	else if (state == PHILO_IS_DEAD)
		print_state(ph, philo->id, " died.\n", &tv);
	sem_post(ph->sem_print.sem);
	return (tv);
}

void	print_error_msg(t_philo_handler *ph, char *msg, bool post_error)
{
	sem_wait(ph->sem_print.sem);
	if (post_error)
		sem_post(ph->sem_error.sem);
	ft_puterr(msg);
	sem_post(ph->sem_print.sem);
}
