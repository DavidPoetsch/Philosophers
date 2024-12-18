/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:12 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/18 16:12:18 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ms_to_us(unsigned int ms)
{
	return (ms * 1000);
}

long	get_time_duration_in_ms(t_tv tv_start, t_tv tv_end)
{
	long	seconds;
	long	microseconds;
	long	milliseconds;

	if (tv_start.tv_sec > tv_end.tv_sec)
		return (-1);
	seconds = tv_end.tv_sec - tv_start.tv_sec;
	microseconds = tv_end.tv_usec - tv_start.tv_usec;
	milliseconds = (seconds * 1000) + (microseconds / 1000);
	return (milliseconds);
}

int	get_current_time(t_tv *tv)
{
	if (gettimeofday(tv, NULL) != 0)
	{
		ft_puterr(ERR_GETTIMEOFDAY);
		return (ERROR);
	}
	return (SUCCESS);
}
