/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:05:46 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/28 14:12:00 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "defines.h"
# include "enums.h"
# include "philo_errors.h"
# include "structs.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Init

void				init_args(t_args *args, int argc, char *argv[]);
int					init_philos(t_args args, t_philo_handler *ph);
int					init_start_time(t_philo_handler *ph);

// Parse input

int					parse_arguments(t_args args, t_philo_handler *ph);

// Philo life

void				*t_philo_life(void *p);
int					start_philo_processes(t_philo_handler *ph);
void				start_philo_threads(t_philo_handler *ph, t_philo *philo);
bool				sim_running(t_philo_handler *ph, t_philo *philo);
void				send_finished(t_philo_handler *ph, t_philo *philo);
void				update_last_meal_time(t_philo *philo, t_tv *tv);
void				put_forks_down(t_philo_handler *ph);
int					philo_usleep(t_philo *philo, unsigned long long us_sleep);
void				*t_mon_philo_death(void *p);
void				*t_mon_philo_state(void *p);

// Philo state

unsigned long long	print_philo_state(t_philo_handler *ph, t_philo *philo,
						int state);
void				print_error_msg(t_philo_handler *ph, char *msg,
						bool post_error);

// Simulation monitoring

int					post_simulation_finished(t_philo_handler *ph);
void				sim_monitoring(t_philo_handler *ph);

// Utils

char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_itoa(int n);
bool				str_is_numeric(char *str);
int					ft_atoi(const char *nptr);
bool				int_check(const char *str);
size_t				ft_strlen(const char *str);
int					ft_putstr(char *str);
int					ft_puterr(char *str);
void				ft_putnbr(size_t n);
void				ft_swap_ptr(void **p1, void **p2);

// Semaphore utils

int					init_semaphores(t_philo_handler *ph);
int					close_semaphores(t_philo_handler *ph);
int					init_semaphore(t_sem *sem, char *name, int value);
int					close_semaphore(t_sem *sem, bool unlink);
void				set_int_sem(t_int_sem *t_sem, int value);
void				get_int_sem(t_int_sem *t_sem, int *value);
void				set_tv_sem(t_tv_sem *t_sem, t_tv tv_new);
void				get_tv_sem(t_tv_sem *t_sem, t_tv *tv_res);

// Thread utils

int					t_create(t_thread_info *thread_info,
						void *(*start_routine)(void *), void *arg);
void				t_join(t_thread_info *thread_info);

// Time utils

unsigned int		ms_to_us(unsigned int ms);
unsigned long long	get_time_duration_in_us(t_tv tv_start, t_tv tv_end);
unsigned long long	get_curr_us(void);

// Wrapper

t_ptr_wrapper		void_ptr_wrapper(t_philo_handler *ph, t_philo *philo);

// Wait utils

int					wait_philo_processes(t_philo_handler *ph);
void				wait_for_process(t_process *process);

// Clean up

void				philo_free(t_philo_handler *ph);
void				philo_exit(t_philo_handler *ph, int res);

// Error handler
int					start_error_handler_thread(t_philo_handler *ph);
void				join_error_handler_thread(t_philo_handler *ph);
#endif
