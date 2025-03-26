/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_ptr_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:22:05 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:35:04 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_ptr_wrapper	void_ptr_wrapper(t_philo_handler *ph, t_philo *philo)
{
	t_ptr_wrapper	wrapper;

	wrapper.ptr_ph = ph;
	wrapper.ptr_philo = philo;
	return (wrapper);
}
