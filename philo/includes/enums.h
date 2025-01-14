/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:07:15 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/14 09:49:41 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_philo_state
{
	PHILO_IS_ALIVE,
	PHILO_HAS_TAKEN_FORK,
	PHILO_IS_EATING,
	PHILO_IS_SLEEPING,
	PHILO_IS_THINKING,
	PHILO_IS_DEAD,
};

enum e_return_values
{
	ERROR = 0,
	SUCCESS = 1,
};

enum e_mutex_state
{
	M_STATE_UNDEFINED,
	M_STATE_INIT,
	M_STATE_DESTROYED,
};

enum e_simulation_state
{
	SIM_RUNING,
	SIM_FINISHED,
};

enum e_state_philo_handler
{
	PH_STATE_UNDEFINED,
	PH_STATE_PHILOS_INIT,
	PH_STATE_PHILOS_FREE,
};

#endif
