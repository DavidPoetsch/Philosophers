/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:07:15 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 16:19:19 by dpotsch          ###   ########.fr       */
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

enum e_eat_reaquest
{
	EATING_ALLOWED,
	EATING_DENIED,
};

enum e_fork_state
{
	FORK_AVAILABLE,
	FORK_UNAVAILABLE,
};

enum e_mutex_return_value
{
	M_LOCK_SUCCESS = 0,
};

enum e_simulation_state
{
	SIM_RUNING,
	SIM_FINISHED,
};

#endif
