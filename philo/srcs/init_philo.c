/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 11:19:18 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	alloc_forks(t_philo_handler *ph)
{
	if (!ph)
		return (ERROR);
	ph->forks = (t_mutex *)malloc(ph->philos * sizeof(t_mutex));
	if (!ph->forks)
	{
		ft_puterr(ERR_MALLOC_FORKS);
		free(ph->philo_lst);
		ph->philo_lst = NULL;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	alloc_philos(t_philo_handler *ph)
{
	int	i;

	if (!ph)
		return (ERROR);
	ph->state = PH_STATE_UNDEFINED;
	ph->philo_lst = (t_philo *)malloc(ph->philos * sizeof(t_philo));
	if (!ph->philo_lst)
	{
		ft_puterr(ERR_MALLOC_PHILOS);
		return (ERROR);
	}
	if (alloc_forks(ph) == ERROR)
		return (ERROR);
	i = 0;
	while (i < ph->philos)
	{
		memset(&ph->philo_lst[i], 0, sizeof(t_philo));
		ph->philo_lst[i].id = i + 1;
		ph->philo_lst[i].ph = ph;
		ph->philo_lst[i].fork1 = &ph->forks[i];
		i++;
	}
	ph->state = PH_STATE_PHILOS_INIT;
	return (SUCCESS);
}

/**
 * @brief ### Assign forks to philosophers.
 * 
 * - The forks will be swaped for philos with odd numbers to prevent deadlock.
 *
 * - Deadlock example: All Pick up left fork at the same time.
 * @param ph philo_handler struct
 * @return int SUCCESS or ERROR
 */
static int	assign_forks(t_philo_handler *ph)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (i + 1 == ph->philos)
			ph->philo_lst[i].fork2 = ph->philo_lst[0].fork1;
		else
			ph->philo_lst[i].fork2 = ph->philo_lst[i + 1].fork1;
		i++;
	}
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (philo->id % 2 != 0)
		{
			ft_swap_ptr((void **)&philo->fork1, (void **)&philo->fork2);
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_mutexes(t_philo_handler *ph)
{
	int		res;
	int		i;
	t_philo	*philo;

	res = init_mutex(&ph->m_print);
	if (res == SUCCESS)
		res = init_mutex(&ph->m_sim_state.m);
	if (res == SUCCESS)
		res = init_mutex(&ph->m_error.m);
	i = 0;
	while (res == SUCCESS && i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		res = init_mutex(&philo->m_tv_last_meal.m);
		if (res == SUCCESS)
			res = init_mutex(&ph->forks[i]);
		if (res == SUCCESS)
			res = init_mutex(&philo->m_meals.m);
		i++;
	}
	return (res);
}

/**
 * @brief ### Initialize philo handler structure.
 * @param args Program arguments.
 * @param ph philo handler struct.
 * @return int SUCCESS or ERROR.
 */
int	init_philos(t_args args, t_philo_handler *ph)
{
	int	res;

	if (!ph)
		return (ERROR);
	res = parse_arguments(args, ph);
	if (res == SUCCESS)
		res = alloc_philos(ph);
	if (res == SUCCESS)
		res = assign_forks(ph);
	if (res == SUCCESS)
		res = init_mutexes(ph);
	if (res == SUCCESS)
		res = init_start_time(ph);
	if (res == SUCCESS)
		calculate_time_to_think(ph);
	if (res == SUCCESS)
		ph->m_sim_state.value = SIM_RUNING;
	return (res);
}
