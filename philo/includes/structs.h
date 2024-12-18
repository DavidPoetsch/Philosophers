/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 16:54:26 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo_handler	t_philo_handler;
typedef struct s_philo			t_philo;
typedef struct s_args			t_args;
typedef struct s_fork			t_fork;
typedef struct timeval			t_tv;

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
	t_tv						tv_start;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							last_lock_id;
	int							sim_state;
	bool						meal_limit;
	pthread_t					ptid_mon;
	pthread_mutex_t				eat_lock;
	pthread_mutex_t				print_lock;
	pthread_mutex_t				sim_state_lock;
};

struct							s_fork
{
	int							state; //! not used
	pthread_mutex_t				lock;
};

struct							s_philo
{
	int							id;
	pthread_t					ptid;
	int							meals;
	pthread_mutex_t				meals_lock;
	t_tv						tv_last_meal;
	t_fork						*fork1;
	t_fork						*fork2;
	t_philo_handler				*ph;
};

#endif
