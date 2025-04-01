/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:10 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 17:26:38 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef DEBUG
#  define DEBUG false
# endif

// Times

# define USLEEP_PAUSE 250
# define DEATH_CHECK_PAUSE 250

// Sempahore names (philo handler)

# define SEM_NAME_FORKS "/sem_forks"
# define SEM_NAME_FORKS_REQ "/sem_forks_request"
# define SEM_NAME_PRINT "/sem_print"
# define SEM_NAME_PHILO_FIN "/sem_philo_finished"
# define SEM_NAME_STOP_SIM "/sem_stop_sim"
# define SEM_NAME_STOP_FB "/sem_stop_feedback"
# define SEM_NAME_ERROR "/sem_error_philosophers"
# define SEM_NAME_PHILO_START "/sem_philos_started"
# define SEM_NAME_DEATH "/sem_philo_death_lock"

// Sempahore names (philo)

# define SEM_NAME_SIM_STATE "/sem_simulation_state"
# define SEM_NAME_TIME_OF_DEATH "/sem_philo_time_of_death"

// Basics

# define CHILD 0
# define FAILED -1

#endif
