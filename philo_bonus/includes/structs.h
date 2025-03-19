/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/19 12:19:19 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo_handler	t_philo_handler;
typedef struct s_philo			t_philo;
typedef struct s_args			t_args;
typedef struct timeval			t_tv;
typedef struct s_sem			t_sem;
typedef struct s_int_sem		t_int_sem;
typedef struct s_tv_sem			t_tv_sem;
typedef struct s_process		t_process;
typedef struct s_thread_info	t_thread_info;
typedef struct s_ptr_wrapper	t_ptr_wrapper;

struct							s_args
{
	int							argc;
	char						**argv;
	int							i;
};

struct							s_sem
{
	sem_t						*sem;
	int							state;
	char						*name;
	bool						free_name;
};

struct							s_int_sem
{
	int							value;
	t_sem						sem;
};

struct							s_tv_sem
{
	t_tv						tv;
	t_sem						sem;
};

struct							s_process
{
	int							pid;
	int							state;
	int							exit_status;
};

struct							s_thread_info
{
	pthread_t					ptid;
	int							state;
};

struct							s_philo_handler
{
	t_philo						*philo_lst;
	int							philos;
	t_tv						tv_start;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							meals_per_philo;
	bool						meal_limit;
	t_sem						sem_forks_request;
	t_sem						sem_forks;
	t_sem						sem_print;
	t_sem						sem_print_block;
	t_sem						sem_philo_finished;
	t_sem						sem_stop_simulation;
	t_sem						sem_error;
	t_sem						sem_philos_started;
	t_thread_info		t_error_handler;
	bool						is_child;
};

struct							s_philo
{
	int							id;
	int							meals;
	t_process					process;
	t_thread_info				t_philo_life;
	t_thread_info				t_mon_philo_state;
	t_thread_info				t_mon_death;
	t_tv_sem					sem_tv_last_meal;
	t_int_sem					sem_sim_state;
	bool						finished;
};

struct							s_ptr_wrapper
{
	t_philo_handler				*ptr_ph;
	t_philo						*ptr_philo;
};

#endif
