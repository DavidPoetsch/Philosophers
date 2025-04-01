/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:12 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 09:25:32 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

inline	__attribute__((always_inline))
unsigned int	ms_to_us(unsigned int ms)
{
	return (ms * 1000);
}

inline	__attribute__((always_inline))
unsigned long long	get_curr_us(void)
{
	t_tv	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000ULL) + tv.tv_usec);
}
