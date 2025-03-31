/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:05:46 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/31 13:18:41 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "defines.h"
# include "enums.h"
# include "philo_errors.h"
# include "structs.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Init

void				init_args(t_args *args, int argc, char *argv[]);
int					init_philos(t_args args, t_philo_handler **ph);
int					init_start_time(t_philo_handler *ph);
void				calculate_time_to_think(t_philo_handler *ph,
						t_philo *philo);

// Mutex utils

int					lock_mutex(t_mutex *mutex);
int					init_mutex(t_mutex *mutex);
int					destroy_mutex(t_mutex *mutex);
int					inc_int_mutex(t_int_mutex *t_mut);
int					set_int_mutex(t_int_mutex *t_mut, int value);
int					get_int_mutex(t_int_mutex *t_mut, int *value);
int					set_ull_mutex(t_ull_mutex *t_mut, unsigned long long value);
int					get_ull_mutex(t_ull_mutex *t_mut,
						unsigned long long *ull_res);

// Parse input
int					parse_arguments(t_args args, t_input *input);

// Philo life

void				*philo_life(void *p);
void				put_forks_down(t_philo *philo);
void				update_time_to_die(t_philo *philo,
						unsigned long long us_curr);
int					philo_usleep(t_philo_handler *ph,
						unsigned long long us_sleep);
int					start_philo_threads(t_philo_handler *ph);
bool				sim_running(t_philo_handler *ph, t_philo *philo);
// Monitoring

void				*philo_monitoring(void *p);
void				set_state_finished(t_philo_handler *ph);
int					start_monitoring_thread(t_philo_handler *ph);

// Print philo state

unsigned long long	print_philo_state(t_philo_handler *ph, int id, int state);
void				print_philo_state_fork(t_philo_handler *ph, t_philo *philo,
						int fork);
void				print_error(t_philo_handler *ph, char *msg, int error);

// Utils

int					ft_atoi(const char *nptr);
bool				str_is_numeric(char *str);
bool				int_check(const char *str);
size_t				ft_strlen(const char *str);
int					ft_puterr(char *str);
void				ft_swap_ptr(void **p1, void **p2);

// Thread utils

int					t_create(t_thread_info *thread_info,
						void *(*start_routine)(void *), void *arg);
void				t_join(t_thread_info *thread_info);

// Time utils
unsigned int		ms_to_us(unsigned int ms);
unsigned long long	get_time_duration_in_ms(t_tv tv_start, t_tv tv_end);
unsigned long long	get_curr_us(void);

// Clean

int					philo_free(t_philo_handler *ph);
void				join_philo_threads(t_philo_handler *ph);

#endif
