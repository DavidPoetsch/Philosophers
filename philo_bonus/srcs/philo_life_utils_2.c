/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:25:25 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 12:27:10 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	put_forks_down(t_philo_handler *ph)
{
	sem_post(ph->sem_forks.sem);
	sem_post(ph->sem_forks.sem);
}
