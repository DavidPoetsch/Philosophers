/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:52:34 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 16:10:24 by dpotsch          ###   ########.fr       */
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
# define ERR_GETTIMEOFDAY "philo: gettimeofday: failed to get time.\n"
# define ERR_MUTEX_INIT "philo: mutex initialization failed.\n"
#endif
