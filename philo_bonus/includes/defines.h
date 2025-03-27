/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:10 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 16:58:11 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef DEBUG
#  define DEBUG false
# endif

// Times

# define US_DEATH_CHECK_PAUSE 200
# define US_USLEEP_PAUSE 100
# define MS_CHECK_SIM_STATE 1234

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
# define SEM_NAME_LAST_MEAL "/sem_philo_last_meal_time"

// Basics

# define CHILD 0
# define FAILED -1

#endif
