/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_ptr_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:22:05 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 20:08:42 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/**
 * @brief ### Wraps philo handler and philo struct in one struct.
 * 
 * - Better to pass multiple pointers to threads.
 * 
 * @param ph philo handler struct
 * @param philo philo struct
 * @return t_ptr_wrapper new struct
 */
t_ptr_wrapper	void_ptr_wrapper(t_philo_handler *ph, t_philo *philo)
{
	t_ptr_wrapper	wrapper;

	wrapper.ptr_ph = ph;
	wrapper.ptr_philo = philo;
	return (wrapper);
}
