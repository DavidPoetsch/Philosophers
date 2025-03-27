/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:12 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/27 17:37:53 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned int	ms_to_us(unsigned int ms)
{
	return (ms * 1000);
}

size_t	get_time_duration_in_us(t_tv tv_start, t_tv tv_end)
{
	size_t	seconds;
	size_t	usec;

	if (tv_start.tv_sec > tv_end.tv_sec)
		return (0);
	seconds = tv_end.tv_sec - tv_start.tv_sec;
	usec = tv_end.tv_usec - tv_start.tv_usec;
	return ((seconds * 1000000) + usec);
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
