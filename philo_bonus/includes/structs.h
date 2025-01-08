/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:01:10 by dpotsch          ###   ########.fr       */
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
typedef struct s_process			t_process;

struct							s_args
{
	int							argc;
	char						**argv;
	int							i;
};

struct s_sem
{
	sem_t *sem;
	int	state;
	char *name;
	bool free_name;
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

struct s_process
{
	int pid;
	int state;
	int exit_status;
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
	t_sem						sem_print;
	t_sem						sem_forks;
	t_sem						sem_sim_state;
	pthread_t				ptid_sim_mon;
};

struct							s_philo
{
	int							id;
	int							meals;
	t_philo_handler				*ph;
	t_process					process;
	pthread_t					ptid_mon_sim_state;
	t_int_sem					sem_sim_state;


	t_int_sem	sem_meals;//!not used
	t_tv_sem	sem_tv_last_meal;//!not used
};

#endif
