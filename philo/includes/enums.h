/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:07:15 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/16 17:09:39 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_philo_state
{
	PHILO_STATE_UNDEFINED,
	PHILO_HAS_TAKEN_FORK,
	PHILO_IS_EATING,
	PHILO_IS_SLEEPING,
	PHILO_IS_THINKING,
	PHILO_DIED,
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

#endif
