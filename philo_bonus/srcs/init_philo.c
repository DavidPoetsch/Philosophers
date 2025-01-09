/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/09 12:43:44 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
	int i;

	ph->philo_lst = (t_philo *)malloc(ph->philos * sizeof(t_philo));
	if (!ph->philo_lst)
		return (ERROR);
	i = 0;
	while (i < ph->philos)
	{
		ph->philo_lst[i].id = i + 1;
		ph->philo_lst[i].ph = ph;
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
		philo->sem_tv_last_meal.tv.tv_sec = ph->tv_start.tv_sec;
		philo->sem_tv_last_meal.tv.tv_usec = ph->tv_start.tv_usec;
		philo->sem_meals.value = 0;
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
		res = init_semaphores(ph);
	if (res != ERROR)
		res = init_start_time(ph);
	return (res);
}

