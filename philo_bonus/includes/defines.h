/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:17:10 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/13 16:32:27 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define DEBUG false

# define TIME_TO_TAKE_FORKS 0
# define MS_SIM_SLEEP 2
# define MS_MON_SLEEP 5
# define MS_DEATH_CHECK 7

// SEMAPHORE NAMES
# define SEM_NAME_FORKS "/sem_forks"
# define SEM_NAME_FORKS_REQ "/sem_forks_request"
# define SEM_NAME_PRINT "/sem_print"
# define SEM_NAME_PRINT_BLOCK "/sem_print_block"

# define SEM_NAME_PHILO_FIN "/sem_philo_finished"
# define SEM_NAME_STOP_SIM "/sem_stop_sim"

# define SEM_NAME_SIM_STATE "/sem_simulation_state"     //! delete
# define SEM_NAME_MEALS "/sem_philo_meals"              //! delete
# define SEM_NAME_LAST_MEAL "/sem_philo_last_meal_time" //! delete

# define CHILD 0
# define FAILED -1

#endif
