/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:05:46 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 17:04:10 by dpotsch          ###   ########.fr       */
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

# define TIME_TO_TAKE_FORKS 10

void			*philo_life(void *p);
int				ask_for_eat_permission(t_philo_handler *ph, t_philo *philo);
void			update_philo_meal_stat(t_philo *philo);

// Init philo
int				init_philos(t_args args, t_philo_handler *ph);

// Utils
size_t			ft_strlen(char *str);
int				ft_puterr(char *str);
void			print_philo_state(t_philo_handler *ph, int id, int state);
void			init_args(t_args *args, int argc, char *argv[]);
int				ft_atoi(const char *nptr);

unsigned int	ms_to_us(unsigned int ms);
long			get_time_duration_in_ms(t_tv tv_start, t_tv tv_end);

int				start_monitoring_thread(t_philo_handler *ph);
#endif
