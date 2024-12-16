/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:05:46 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/16 16:18:25 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "philo_errors.h"
# include "enums.h"
# include "structs.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

// Init philo
int	init_philos(t_args args, t_philo_handler *ph);

// Utils
size_t	ft_strlen(char *str);
int		ft_puterr(char *str);
void	print_philo_state(t_philo_handler *ph, int id, int state);
void	init_args(t_args *args, int argc, char *argv[]);
int	ft_atoi(const char *nptr);

unsigned int ms_to_us(unsigned int ms);

#endif


