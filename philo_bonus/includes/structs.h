/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:53:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/07 16:35:51 by dpotsch          ###   ########.fr       */
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
typedef struct s_int_sem		t_int_sem;
typedef struct s_tv_sem			t_tv_sem;

struct							s_args
{
	int							argc;
	char						**argv;
	int							i;
};

struct							s_int_sem
{
	int							value;
	sem_t						sem;
};

struct							s_tv_sem
{
	t_tv						tv;
	sem_t						sem;
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
	pthread_t					ptid_mon;
	sem_t						*sem_print;
	sem_t						*sem_forks;
	t_int_sem					sem_sim_state;
};

struct							s_philo
{
	int							id;
	pthread_t					ptid;
	t_int_sem					sem_meals;
	t_tv_sem					sem_tv_last_meal;
	t_philo_handler				*ph;
};

#endif
