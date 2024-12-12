/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/12 15:19:16 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdio.h>

typedef struct s_philo_handler	t_philo_handler;
typedef struct s_philo			t_philo;

struct							s_philo_handler
{
	size_t						philos;
	size_t						forks;
	size_t						meals_per_philo;
	size_t						time_to_die;
	size_t						time_to_eat;
	size_t						time_to_sleep;
};

struct							s_philo
{
	int							id;
	char						*name;
	int							*value;
	pthread_mutex_t				*fork;
};

#endif
