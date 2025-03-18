/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:10 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/18 10:32:18 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define DEBUG false

// Times

# define MS_DEATH_CHECK 5
# define US_SIM_SLEEP 500
# define US_DELAY_THINKING 1000
# define MS_CHECK_SIM_STATE 1000

// Sempahore names

# define SEM_NAME_FORKS "/sem_forks"
# define SEM_NAME_FORKS_REQ "/sem_forks_request"
# define SEM_NAME_PRINT "/sem_print"
# define SEM_NAME_PRINT_BLOCK "/sem_print_block"

# define SEM_NAME_PHILO_FIN "/sem_philo_finished"
# define SEM_NAME_STOP_SIM "/sem_stop_sim"
# define SEM_ERROR "/sem_error_philosophers"

# define SEM_NAME_SIM_STATE "/sem_simulation_state"     //! delete
# define SEM_NAME_MEALS "/sem_philo_meals"              //! delete
# define SEM_NAME_LAST_MEAL "/sem_philo_last_meal_time" //! delete

// Basics

# define CHILD 0
# define FAILED -1

#endif
