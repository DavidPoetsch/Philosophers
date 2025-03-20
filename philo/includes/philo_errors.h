/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:52:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/20 16:47:24 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERRORS_H
# define PHILO_ERRORS_H

# define ERR_INVALID_ARGS "philo: invalid number of arguments.\n"
# define ERR_INVALID_PHILOS "philo: invalid number of philosophers.\n"
# define ERR_INVALID_TTD "philo: invalid time to die.\n"
# define ERR_INVALID_TTE "philo: invalid time to eat.\n"
# define ERR_INVALID_TTS "philo: invalid time to sleep.\n"
# define ERR_INVALID_MEALS "philo: invalid amount of meals per philosopher.\n"
# define ERR_MALLOC_PHILOS "philo: failed to allocate philos.\n"
# define ERR_MALLOC_FORKS "philo: failed to allocate forks.\n"
# define ERR_GETTIMEOFDAY "philo: gettimeofday: failed to get time.\n"

# define ERR_MUTEX_INIT "philo: mutex initialization failed.\n"
# define ERR_MUTEX_LOCK "philo: mutex lock failed.\n"
# define ERR_MUTEX_DESTROY "philo: mutex destroy failed.\n"

# define ERR_CREATE_THREAD "philo: failed to create thread\n"

# define ERR_MUT_NOT_INIT "philo: mutex is not properly initialized\n"
# define ERR_MUT_DLK "philo: deadlock detected\n"
# define ERR_MUT_DLK "philo: deadlock detected\n"
# define ERR_MUTEX "philo: failed to lock mutex\n"

#endif
