/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_philo_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:13:11 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/21 13:00:34 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Join all threads.
 *
 * - join philo threads
 *
 * - join monitoring thread
 * @param ph
 */
void	join_philo_threads(t_philo_handler *ph)
{
	int	i;

	i = 0;
	while (i < ph->philos)
	{
		t_join(&ph->philo_lst[i].t_philo);
		i++;
	}
	t_join(&ph->t_mon);
}
