/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:52:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/24 09:34:11 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ERRORS_H
# define PHILO_ERRORS_H

# define ERR_MALLOC_PHILOS "philo: failed to allocate philos.\n"
# define ERR_INVALID_ARGS "philo: invalid number of arguments.\n"
# define ERR_INVALID_PHILOS "philo: invalid number of philosophers.\n"
# define ERR_INVALID_TTD "philo: invalid time to die.\n"
# define ERR_INVALID_TTE "philo: invalid time to eat.\n"
# define ERR_INVALID_TTS "philo: invalid time to sleep.\n"
# define ERR_INVALID_MEALS "philo: invalid amount of meals per philosopher.\n"
# define ERR_GETTIMEOFDAY "philo: gettimeofday: failed to get time.\n"
# define ERR_SEM_INIT \
	"philo: init_semaphore: semaphore initialization failed.\n"
# define ERR_SEM_CLOSE "philo: close_semaphore: semaphore close failed.\n"
# define ERR_SEM_UNLINK "philo: close_semaphore: semaphore unlink failed.\n"
# define ERR_CREATE_SEM_NAME \
	"philo: create_sem_name: semaphore initialization failed.\n"
# define ERR_FORK_PROCESS "philo: fork process failed\n"
# define ERR_CREATE_THREAD "philo: failed to create thread\n"
#endif
