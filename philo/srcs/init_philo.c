/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 16:06:23 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

static int get_philos(t_args args, t_philo_handler *ph)
{
	ph->philos = ft_atoi(args.argv[1]);
	if (ph->philos <= 0)
	{
		ft_puterr(ERR_INVALID_PHILOS);
		return (ERROR);
	}
	return (SUCCESS);
}

static int get_times(t_args args, t_philo_handler *ph)
{
	ph->time_to_die = ft_atoi(args.argv[2]);
	if (ph->time_to_die <= 0)
	{
		ft_puterr(ERR_INVALID_TTD);
		return (ERROR);
	}
	ph->time_to_eat = ft_atoi(args.argv[3]);
	if (ph->time_to_eat <= 0)
	{
		ft_puterr(ERR_INVALID_TTE);
		return (ERROR);
	}
	ph->time_to_sleep = ft_atoi(args.argv[4]);
	if (ph->time_to_sleep <= 0)
	{
		ft_puterr(ERR_INVALID_TTS);
		return (ERROR);
	}
	return (SUCCESS);
}

static int get_meals_per_philo(t_args args, t_philo_handler *ph)
{
	if (args.argc < 6)
	{
		ph->meals_per_philo = 0;
		ph->meal_limit = false;
		return (SUCCESS);
	}
	ph->meal_limit = true;
	ph->meals_per_philo = ft_atoi(args.argv[5]);
	if (ph->meals_per_philo <= 0)
	{
		ft_puterr(ERR_INVALID_MEALS);
		return (ERROR);
	}
	return (SUCCESS);
}

int alloc_philos(t_philo_handler *ph)
{
	t_fork	*forks;
	int i;

	ph->philo_lst = (t_philo *)malloc(ph->philos * sizeof(t_philo));
	if (!ph->philo_lst)
		return (ERROR);
	forks = (t_fork *)malloc(ph->philos * sizeof(t_fork));
	if (!forks)
		return (ERROR);
	i = 0;
	while (i < ph->philos)
	{
		ph->philo_lst[i].id = i + 1;
		ph->philo_lst[i].ph = ph;
		ph->philo_lst[i].fork1 = &forks[i];
		i++;
	}
	return (SUCCESS);
}

static int	init_philo(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		init_mutex(&philo->fork1->lock);
		init_mutex(&philo->meals_lock);
		philo->fork1->state = FORK_AVAILABLE;
		if (i + 1 == ph->philos)
			ph->philo_lst[i].fork2 = ph->philo_lst[0].fork1;
		else
			ph->philo_lst[i].fork2 = ph->philo_lst[i + 1].fork1;
		i++;
	}
	return (SUCCESS);
}

static int init_mutexes(t_philo_handler *ph)
{
	init_mutex(&ph->print_lock);
	init_mutex(&ph->eat_lock);
	init_mutex(&ph->sim_state_lock);
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
		philo->tv_last_meal.tv_sec = ph->tv_start.tv_sec;
		philo->tv_last_meal.tv_usec = ph->tv_start.tv_usec;
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
	res = SUCCESS;
	if (args.argc < 5 || args.argc > 6)
	{
		ft_puterr(ERR_INVALID_ARGS);
		res = ERROR;
	}
	if (res != ERROR)
		res = get_philos(args, ph);
	if (res != ERROR)
		res = get_times(args, ph);
	if (res != ERROR)
		res = get_meals_per_philo(args, ph);
	if (res != ERROR)
		res = alloc_philos(ph);
	if (res != ERROR)
		res = init_philo(ph);
	if (res != ERROR)
		res = init_mutexes(ph);
	if (res != ERROR)
		res = init_start_time(ph);
	return (res);
}

