/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:07:15 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/26 10:33:17 by dpotsch          ###   ########.fr       */
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
	SUCCESS = 0,
	ERROR = 1,
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

enum	e_thread_create_return
{
	STATE_THREAD_UNDEFINED,
	STATE_THREAD_FAILED_TO_CREATE,
	STATE_THREAD_CREATED,
	STATE_THREAD_JOINED,
};

enum e_philo_fork_state
{
	PHILO_HAS_NO_FORKS,
	PHILO_TOOK_FORK1,
	PHILO_TOOK_FORK2,
};

#endif