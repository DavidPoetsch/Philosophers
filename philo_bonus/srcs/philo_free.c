/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:17:10 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/03 09:10:32 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_free(t_philo_handler *ph)
{
	close_semaphores(ph);
	if (ph->philo_lst != NULL)
		free(ph->philo_lst);
}

void	philo_exit(t_philo_handler *ph, int res)
{
	close_semaphores(ph);
	if (ph->philo_lst != NULL)
		free(ph->philo_lst);
	exit(res);
}
