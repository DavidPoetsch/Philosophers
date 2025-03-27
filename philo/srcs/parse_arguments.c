/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:41:16 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 16:56:08 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	parse_number(char *arg)
{
	if (!int_check(arg))
		return (-1);
	if (!str_is_numeric(arg))
		return (-1);
	return (ft_atoi(arg));
}

static int	get_arg_philos(t_args args, t_philo_handler *ph)
{
	ph->philos = parse_number(args.argv[1]);
	if (ph->philos <= 0)
	{
		ft_puterr(ERR_INVALID_PHILOS);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	get_arg_times(t_args args, t_philo_handler *ph)
{
	ph->time_to_die = parse_number(args.argv[2]);
	if (ph->time_to_die <= 0)
	{
		ft_puterr(ERR_INVALID_TTD);
		return (ERROR);
	}
	ph->time_to_eat = parse_number(args.argv[3]);
	if (ph->time_to_eat <= 0)
	{
		ft_puterr(ERR_INVALID_TTE);
		return (ERROR);
	}
	ph->time_to_sleep = parse_number(args.argv[4]);
	if (ph->time_to_sleep <= 0)
	{
		ft_puterr(ERR_INVALID_TTS);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	get_arg_meals_per_philo(t_args args, t_philo_handler *ph)
{
	if (args.argc < 6)
	{
		ph->meals_per_philo = 0;
		ph->meal_limit = false;
		return (SUCCESS);
	}
	ph->meal_limit = true;
	ph->meals_per_philo = parse_number(args.argv[5]);
	if (ph->meals_per_philo <= 0)
	{
		ft_puterr(ERR_INVALID_MEALS);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_arguments(t_args args, t_philo_handler *ph)
{
	int	res;

	if (!ph)
		return (ERROR);
	res = SUCCESS;
	if (args.argc < 5 || args.argc > 6)
	{
		ft_puterr(ERR_INVALID_ARGS);
		res = ERROR;
	}
	if (res == SUCCESS)
		res = get_arg_philos(args, ph);
	if (res == SUCCESS)
		res = get_arg_times(args, ph);
	if (res == SUCCESS)
		res = get_arg_meals_per_philo(args, ph);
	return (res);
}
