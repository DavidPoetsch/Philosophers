/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:01:13 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/13 17:29:43 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		res = init_semaphores(ph);
	if (res != ERROR)
		res = init_start_time(ph);
	return (res);
}
