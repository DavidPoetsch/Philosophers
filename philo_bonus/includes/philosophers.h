/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:05:46 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 16:47:24 by dpotsch          ###   ########.fr       */
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
# include <semaphore.h>
#include <fcntl.h>
# include <sys/wait.h>

# define TIME_TO_TAKE_FORKS 0
# define MS_SIM_SLEEP 3
# define MS_MON_SLEEP 5

// SEMAPHORE NAMES
# define SEM_NAME_FORKS "/sem_forks"
# define SEM_NAME_PRINT "/sem_print"
# define SEM_NAME_SIM_STATE "/sem_simulation_state"
# define SEM_NAME_MEALS "/sem_philo_meals"
# define SEM_NAME_LAST_MEAL "/sem_philo_last_meal_time"

void			philo_life(void *p);
// int				ask_for_eat_permission(t_philo_handler *ph, t_philo *philo);
void			update_meals_eaten(t_philo *philo);
void			update_last_meal_time(t_philo *philo);
int				philo_usleep(t_philo_handler	*ph, int ms_sleep);
int				check_simulation_state(t_philo_handler *ph, t_philo *philo);

// Init philo
int				init_philos(t_args args, t_philo_handler *ph);

// Utils
int				ft_puterr(char *str);
void			print_philo_state(t_philo_handler *ph, int id, int state);
void			init_args(t_args *args, int argc, char *argv[]);
int				ft_atoi(const char *nptr);
void			ft_swap_ptr(void **p1, void **p2);

// Time utils
unsigned int	ms_to_us(unsigned int ms);
size_t			get_time_duration_in_ms(t_tv tv_start, t_tv tv_end);
int				get_current_time(t_tv *tv);

// Semaphore utils
int				init_semaphores(t_philo_handler *ph);
int				close_semaphores(t_philo_handler *ph);
int				init_semaphore(t_sem *sem, int value);
int				close_semaphore(t_sem *sem);
int				set_int_sem(t_int_sem *t_sem, int value);
int				get_int_sem(t_int_sem *t_sem, int *value);
int				set_tv_sem(t_tv_sem *t_sem, t_tv tv_new);
int				get_tv_sem(t_tv_sem *t_sem, t_tv *tv_res);

// LIBFT
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

void	wait_for_process(t_process *process);


int	start_philo_mon_thread(t_philo *philo);
int	start_sim_mon_thread(t_philo_handler *ph);
#endif
