/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/16 16:57:50 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo_handler	t_philo_handler;
typedef struct s_philo			t_philo;
typedef struct s_args			t_args;
typedef struct s_fork			t_fork;

struct							s_args
{
	int							argc;
	char						**argv;
	int							i;
};

struct							s_philo_handler
{
	t_philo						*philo_lst;
	int							philos;
	int							meals_per_philo;
	struct timeval				tv_start;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							last_lock_id;
	pthread_mutex_t				lock;
	pthread_mutex_t				print_lock;
};

struct							s_fork
{
	int							state;
	pthread_mutex_t				lock;
};

struct							s_philo
{
	int							id;
	char						*name;
	int							meals;
	pthread_t					ptid;
	t_fork						*fork1;
	t_fork						*fork2;

	t_philo_handler				*ph;
};

#endif
