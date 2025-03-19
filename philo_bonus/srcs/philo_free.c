/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:17:10 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 12:45:01 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_free(t_philo_handler *ph)
{
	if (ph->philo_lst)
		free(ph->philo_lst);
}

void	philo_exit(t_philo_handler *ph, int res)
{
	close_semaphores(ph);
	if (ph->philo_lst)
		free(ph->philo_lst);
	exit(res);
}
