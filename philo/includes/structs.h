/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 10:10:46 by dpotsch          ###   ########.fr       */
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
typedef struct s_ull_mutex		t_ull_mutex;
typedef struct s_mutex			t_mutex;
typedef struct s_thread_info	t_thread_info;
typedef struct s_input			t_input;

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

struct							s_ull_mutex
{
	unsigned long long			value;
	t_mutex						m;
};

struct							s_input
{
	int							philos;
	unsigned long long			time_to_die;
	unsigned long long			time_to_eat;
	unsigned long long			time_to_sleep;
	int							meals_per_philo;
};

struct							s_philo_handler
{
	t_philo						*philo_lst;
	int							philos;
	unsigned long long			start_time;
	int							meals_per_philo;
	bool						meal_limit;
	t_thread_info				t_mon;
	t_mutex						m_print;
	t_int_mutex					m_sim_state;
	t_int_mutex					m_error;
	t_int_mutex					m_all_philos_finished;
	int							state;
};

struct							s_philo
{
	int							id;
	t_thread_info				t_philo;
	t_int_mutex					m_meals;
	t_ull_mutex					m_time_of_death;
	unsigned long long			local_time_of_death;
	unsigned long long			time_to_die;
	unsigned long long			time_to_eat;
	unsigned long long			time_to_sleep;
	unsigned long long			time_to_think;
	t_mutex						own_fork;
	t_mutex						*fork1;
	t_mutex						*fork2;
	t_philo_handler				*ph;
	int							fork_state;
};

#endif
