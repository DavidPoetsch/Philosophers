/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:52 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/12 16:57:01 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# define SECONDS_PER_MIN 60
# define SECONDS_PER_HOUR 3600
# define SECONDS_PER_DAY 86400

static const unsigned int	month_lengths[] = {31, 28, 31, 30, 31, 30, 31, 31,
		30, 31, 30, 31};

typedef struct s_time		t_time;
struct						s_time
{
	unsigned int			h;
	unsigned int			m;
	unsigned int			s;
	unsigned int			millis;
	unsigned int			year;
	unsigned int			month;
	unsigned int			day;
};

t_time						get_timestamp(void);

#endif
