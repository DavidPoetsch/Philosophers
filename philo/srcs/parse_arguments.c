/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:41:16 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/31 11:30:56 by dpotsch          ###   ########.fr       */
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

static int	get_arg_philos(t_args args, t_input *input)
{
	input->philos = parse_number(args.argv[1]);
	if (input->philos <= 0)
	{
		ft_puterr(ERR_INVALID_PHILOS);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	get_arg_times(t_args args, t_input *input)
{
	input->time_to_die = parse_number(args.argv[2]);
	if (input->time_to_die <= 0)
	{
		ft_puterr(ERR_INVALID_TTD);
		return (ERROR);
	}
	input->time_to_eat = parse_number(args.argv[3]);
	if (input->time_to_eat <= 0)
	{
		ft_puterr(ERR_INVALID_TTE);
		return (ERROR);
	}
	input->time_to_sleep = parse_number(args.argv[4]);
	if (input->time_to_sleep <= 0)
	{
		ft_puterr(ERR_INVALID_TTS);
		return (ERROR);
	}
	input->time_to_die *= 1000ULL;
	input->time_to_eat *= 1000ULL;
	input->time_to_sleep *= 1000ULL;
	return (SUCCESS);
}

static int	get_arg_meals_per_philo(t_args args, t_input *input)
{
	if (args.argc < 6)
	{
		input->meals_per_philo = -1;
		return (SUCCESS);
	}
	input->meals_per_philo = parse_number(args.argv[5]);
	if (input->meals_per_philo <= 0)
	{
		ft_puterr(ERR_INVALID_MEALS);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_arguments(t_args args, t_input *input)
{
	int	res;

	if (!input)
		return (ERROR);
	res = SUCCESS;
	if (args.argc < 5 || args.argc > 6)
	{
		ft_puterr(ERR_INVALID_ARGS);
		res = ERROR;
	}
	if (res == SUCCESS)
		res = get_arg_philos(args, input);
	if (res == SUCCESS)
		res = get_arg_times(args, input);
	if (res == SUCCESS)
		res = get_arg_meals_per_philo(args, input);
	return (res);
}
