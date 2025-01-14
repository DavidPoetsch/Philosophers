/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/14 10:49:42 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

static int alloc_forks(t_philo_handler *ph)
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

static int alloc_philos(t_philo_handler *ph)
{
	int i;

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
		ph->philo_lst[i].id = i + 1;
		ph->philo_lst[i].ph = ph;
		ph->philo_lst[i].fork1 = &ph->forks[i];
		i++;
	}
	ph->state = PH_STATE_PHILOS_INIT;
	return (SUCCESS);
}

/**
 * @brief Assign forks to philosophers.
 *        The forks will be swaped for philos with even numbers
 *        to prevent deadlock.
 *        Deadlock example: All Pick up left fork at the same time.
 * @param ph philo_handler.
 * @return int result.
 */
static int	assign_forks(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		if (i + 1 == ph->philos)
			ph->philo_lst[i].fork2 = ph->philo_lst[0].fork1;
		else
			ph->philo_lst[i].fork2 = ph->philo_lst[i + 1].fork1;
		if (philo->id % 2 == 0)
			ft_swap_ptr((void **)&philo->fork1, (void **)&philo->fork2);
		i++;
	}
	return (SUCCESS);
}

static int init_mutexes(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;

	init_mutex(&ph->m_print);
	init_mutex(&ph->m_sim_state.m);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		init_mutex(&philo->m_meals.m);
		init_mutex(&philo->m_tv_last_meal.m);
		init_mutex(&ph->forks[i]);
		i++;
	}
	return (SUCCESS);
}

static int init_start_time(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;

	if (gettimeofday(&ph->tv_start, NULL) != 0)
	{
		ft_puterr(ERR_GETTIMEOFDAY);
		return (ERROR);
	}
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		philo->m_tv_last_meal.tv.tv_sec = ph->tv_start.tv_sec;
		philo->m_tv_last_meal.tv.tv_usec = ph->tv_start.tv_usec;
		philo->m_meals.value = 0;
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief ./philo [PHILOS] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP].
*  OPTIONAL [number_of_times_each_philosopher_must_eat].
 * @param args
 * @param ph
 * @return int
 */
int	init_philos(t_args args, t_philo_handler *ph)
{
	int res;

	if (!ph)
		return (ERROR);
	res = parse_arguments(args, ph);
	if (res != ERROR)
		res = alloc_philos(ph);
	if (res != ERROR)
		res = assign_forks(ph);
	if (res != ERROR)
		res = init_mutexes(ph);
	if (res != ERROR)
		res = init_start_time(ph);
	return (res);
}

