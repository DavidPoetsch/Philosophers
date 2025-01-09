/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:07:15 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/09 19:44:12 by dpotsch          ###   ########.fr       */
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

enum e_simulation_state
{
	SIM_RUNING,
	SIM_FINISHED,
};

enum e_semaphore_state
{
	SEM_STATE_FAILED,
	SEM_STATE_OPEN,
	SEM_STATE_CLOSED,
	SEM_STATE_UNLINKED,
};

enum e_state_process
{
	STATE_PROCESS_INIT,
	STATE_PROCESS_FORKED,
	STATE_PROCESS_FORK_FAILED,
	STATE_PROCESS_FINISHED,
};

enum e_thread_create_return
{
	STATE_THREAD_UNDEFINED,
	STATE_THREAD_FAILED_TO_CREATE,
	STATE_THREAD_CREATED,
	STATE_THREAD_JOINED,
};


#endif
