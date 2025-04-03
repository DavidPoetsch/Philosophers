/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/03 09:25:06 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_philo_handler(t_philo_handler *ph, t_input input)
{
	ph->time_to_die = input.time_to_die;
	ph->time_to_eat = input.time_to_eat;
	ph->time_to_sleep = input.time_to_sleep;
	ph->philos = input.philos;
	ph->meals_per_philo = input.meals_per_philo;
	ph->meal_limit = (input.meals_per_philo > 0);
}

static int	alloc_philos(t_philo_handler *ph)
{
	int	i;

	ph->philo_lst = (t_philo *)malloc(ph->philos * sizeof(t_philo));
	if (!ph->philo_lst)
	{
		ft_puterr(ERR_MALLOC_PHILOS);
		return (ERROR);
	}
	i = 0;
	while (i < ph->philos)
	{
		memset(&ph->philo_lst[i], 0, sizeof(t_philo));
		ph->philo_lst[i].id = i + 1;
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief ### Initialize philo handler structure.
 * @param args Program arguments.
 * @param ph philo handler struct.
 * @return int SUCCESS or ERROR.
 */
int	init_philos(t_args args, t_philo_handler *ph)
{
	int		res;
	t_input	input;

	if (!ph)
		return (ERROR);
	memset(&input, 0, sizeof(t_input));
	res = parse_arguments(args, &input);
	if (res == SUCCESS)
		init_philo_handler(ph, input);
	if (res == SUCCESS)
		res = alloc_philos(ph);
	if (res == SUCCESS)
		res = init_semaphores(ph);
	if (res == SUCCESS)
		res = init_start_time(ph);
	return (res);
}
