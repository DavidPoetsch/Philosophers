/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:17:06 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/24 16:38:53 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	start_philo_threads(t_philo_handler *ph)
{
	int	res;
	int	i;

	res = SUCCESS;
	i = 0;
	while (res == SUCCESS && i < ph->philos)
	{
		res = t_create(&ph->philo_lst[i].t_philo, philo_life,
				&ph->philo_lst[i]);
		i++;
	}
	if (res != SUCCESS)
		print_error(ph, ERR_CREATE_THREAD, res);
	return (res);
}
