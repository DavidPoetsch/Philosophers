/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:05:46 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/15 09:50:12 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "enums.h"
# include "philo_errors.h"
# include "structs.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DEBUG true
# define TIME_TO_TAKE_FORKS 0
# define MS_SIM_SLEEP 3
# define MS_MON_SLEEP 5

# define M_LOCK_SUCCESS 0

// Parse arguments
int				parse_arguments(t_args args, t_philo_handler *ph);

void			*philo_life(void *p);
// int				ask_for_eat_permission(t_philo_handler *ph, t_philo *philo);
void			update_meals_eaten(t_philo *philo);
void			update_last_meal_time(t_philo *philo);
int				philo_usleep(t_philo_handler	*ph, int ms_sleep);
int				check_simulation_state(t_philo_handler *ph);

// Init philo
int				init_philos(t_args args, t_philo_handler *ph);

// Utils
size_t			ft_strlen(char *str);
int				ft_puterr(char *str);
void			print_philo_state(t_philo_handler *ph, int id, int state);
void			print_philo_state_fork(t_philo_handler *ph, t_philo *philo, int fork);
void			init_args(t_args *args, int argc, char *argv[]);
int				ft_atoi(const char *nptr);
void			ft_swap_ptr(void **p1, void **p2);

// Time utils
unsigned int	ms_to_us(unsigned int ms);
size_t			get_time_duration_in_ms(t_tv tv_start, t_tv tv_end);
int				get_current_time(t_tv *tv);

int				start_monitoring_thread(t_philo_handler *ph);

// Mutex utils
int				init_mutex(t_mutex *mutex);
int				lock_mutex(t_mutex *mutex);
int				destroy_mutex(t_mutex *mutex);
int				set_int_mutex(t_int_mutex *t_mut, int value);
int				get_int_mutex(t_int_mutex *t_mut, int *value);
int				set_tv_mutex(t_tv_mutex *t_mut, t_tv tv_new);
int				get_tv_mutex(t_tv_mutex *t_mut, t_tv *tv_res);

// Philo free
int	philo_free(t_philo_handler *ph);
#endif
