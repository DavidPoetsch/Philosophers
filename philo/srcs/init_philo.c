/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/03 10:01:43 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	alloc_memory_block(t_philo_handler **ph, t_input input)
{
	size_t			mem_size;
	void			*memory_block;
	t_philo_handler	*ph_ptr;

	mem_size = sizeof(t_philo_handler) + input.philos * sizeof(t_philo);
	memory_block = (void*)malloc(mem_size);
	if (!memory_block)
	{
		ft_puterr(ERR_MALLOC_PHILOS);
		return (ERROR);
	}
	memset(memory_block, 0, mem_size);
	ph_ptr = (t_philo_handler *)memory_block;
	ph_ptr->philo_lst = (t_philo *)((char *)memory_block
			+ sizeof(t_philo_handler));
	*ph = ph_ptr;
	return (SUCCESS);
}

static int	init_philos_structs(t_philo_handler *ph, t_input input)
{
	t_philo	*philo;
	int		i;

	if (!ph)
		return (ERROR);
	ph->philos = input.philos;
	ph->meals_per_philo = input.meals_per_philo;
	ph->meal_limit = (input.meals_per_philo > 0);
	ph->m_sim_state.value = SIM_RUNING;
	ph->state = PH_STATE_UNDEFINED;
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		philo->time_to_die = input.time_to_die;
		philo->time_to_eat = input.time_to_eat;
		philo->time_to_sleep = input.time_to_sleep;
		calculate_time_to_think(ph, philo);
		philo->id = i + 1;
		philo->ph = ph;
		philo->fork1 = &philo->own_fork;
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
		res = init_mutex(&philo->m_time_of_death.m);
		if (res == SUCCESS)
			res = init_mutex(&philo->own_fork);
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
int	init_philos(t_args args, t_philo_handler **ph)
{
	t_philo_handler	*new_philo_handler;
	t_input			input;
	int				res;

	new_philo_handler = NULL;
	memset(&input, 0, sizeof(t_input));
	res = parse_arguments(args, &input);
	if (res == SUCCESS)
		res = alloc_memory_block(&new_philo_handler, input);
	if (res == SUCCESS)
		res = init_philos_structs(new_philo_handler, input);
	if (res == SUCCESS)
		res = init_mutexes(new_philo_handler);
	if (res == SUCCESS)
		res = assign_forks(new_philo_handler);
	if (res == SUCCESS)
		res = init_start_time(new_philo_handler);
	*ph = new_philo_handler;
	return (res);
}
