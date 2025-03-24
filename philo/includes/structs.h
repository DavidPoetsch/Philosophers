/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/24 16:32:13 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo_handler	t_philo_handler;
typedef struct s_philo			t_philo;
typedef struct s_args			t_args;
typedef struct timeval			t_tv;
typedef struct s_int_mutex		t_int_mutex;
typedef struct s_tv_mutex		t_tv_mutex;
typedef struct s_mutex			t_mutex;
typedef struct s_thread_info	t_thread_info;

struct							s_thread_info
{
	pthread_t					ptid;
	int							state;
};

struct							s_args
{
	int							argc;
	char						**argv;
	int							i;
};

struct							s_mutex
{
	pthread_mutex_t				m;
	int							state;
};

struct							s_int_mutex
{
	int							value;
	t_mutex						m;
};

struct							s_tv_mutex
{
	t_tv						tv;
	t_mutex						m;
};

struct							s_philo_handler
{
	t_philo						*philo_lst;
	int							philos;
	t_tv						tv_start;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							time_to_think;
	int							meals_per_philo;
	bool						meal_limit;
	t_thread_info				t_mon;
	t_mutex						*forks;
	t_mutex						m_print;
	t_int_mutex					m_sim_state;
	t_int_mutex					m_error;
	int							state;
};

struct							s_philo
{
	int							id;
	t_thread_info				t_philo;
	// t_int_mutex					m_state;
	t_int_mutex					m_meals;
	t_tv_mutex					m_tv_last_meal;
	t_mutex						*fork1;
	t_mutex						*fork2;
	t_philo_handler				*ph;
};

#endif
