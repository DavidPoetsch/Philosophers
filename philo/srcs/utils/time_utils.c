/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:12 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/31 09:35:07 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

inline	__attribute__((always_inline))
unsigned int ms_to_us(unsigned int ms)
{
	return (ms * 1000);
}

inline	__attribute__((always_inline))
unsigned long long get_curr_us(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000ULL) + tv.tv_usec);
}

// inline	__attribute__((always_inline))
// unsigned long long	get_time_duration_in_ms(t_tv tv_start, t_tv tv_end)
// {
// 	unsigned long long	seconds;
// 	unsigned long long	usec;

// 	if (tv_start.tv_sec > tv_end.tv_sec)
// 		return (0);
// 	seconds = tv_end.tv_sec - tv_start.tv_sec;
// 	usec = tv_end.tv_usec - tv_start.tv_usec;
// 	return ((seconds * 1000ULL) + (usec / 1000ULL));
// }

inline	__attribute__((always_inline))
unsigned long long get_time_duration_in_ms(t_tv tv_start, t_tv tv_end)
{
	unsigned long long seconds;
	long long usec;

	if (tv_start.tv_sec > tv_end.tv_sec || 
	    (tv_start.tv_sec == tv_end.tv_sec && tv_start.tv_usec > tv_end.tv_usec))
		return 0;

	seconds = tv_end.tv_sec - tv_start.tv_sec;
	usec = tv_end.tv_usec - tv_start.tv_usec;
	if (usec < 0) {
		seconds -= 1;
		usec += 1000000;
	}

	return (seconds * 1000ULL) + (usec / 1000ULL);
}
