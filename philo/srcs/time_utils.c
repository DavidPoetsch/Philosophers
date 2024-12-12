/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:46:12 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/12 17:02:42 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "time_utils.h"

static bool	is_leap_year(year)
{
	return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0));
}

static void calculate_the_year(t_time * t)
{
	unsigned int	days_in_year;

	if (!t)
		return ;
	t->year = 1970;
	while (1)
	{
		days_in_year = 365;
		if (is_leap_year(t->year))
			days_in_year = 366;
		if (t->s >= days_in_year * SECONDS_PER_DAY)
		{
			t->s -= days_in_year * SECONDS_PER_DAY;
			t->year++;
		}
		else
			break ;
	}
}

static void calculate_the_month(t_time * t)
{
	unsigned int days_in_month;

	t->month = 0;
	if (!t)
		return ;
	while (1)
	{
		days_in_month = month_lengths[t->month];
		if (t->month == 1 && is_leap_year(t->year))
			days_in_month = 29;
		if (t->s >= days_in_month * SECONDS_PER_DAY)
		{
			t->s -= days_in_month * SECONDS_PER_DAY;
			t->month++;
		}
		else
			break ;
	}
	t->month++;
}

static void calculate_the_day(t_time *t)
{
	if (!t)
		return ;
	t->day = t->s / SECONDS_PER_DAY + 1;
	t->s %= SECONDS_PER_DAY;
}

t_time	get_timestamp(void)
{
	t_time			time;
	struct timeval	tv;

	memset(&time, 0, sizeof(t_time));
	if (gettimeofday(&tv, NULL) == 0)
	{
		time.s = tv.tv_sec;
		calculate_the_year(&time);
		calculate_the_month(&time);
		calculate_the_day(&time);
		time.h = time.s / SECONDS_PER_HOUR;
		time.s %= SECONDS_PER_HOUR;
		time.m = time.s / SECONDS_PER_MIN;
		time.s = time.s % SECONDS_PER_MIN;
		time.millis = tv.tv_usec / 1000;
	}
	return (time);
}
