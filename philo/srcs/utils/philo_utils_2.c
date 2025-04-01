/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:38:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 09:12:39 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	str_is_numeric(char *str)
{
	size_t	i;

	if (!str || str[0] == '\0')
		return (false);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	ft_is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

/**
 * @brief				The function converts the initial portion of the string
 *							pointed to by nptr to int.
 * @param nptr	Pointer to a string
 * @return int	The converted value or 0 on error.
 */
int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		number;
	short	is_neg;

	i = 0;
	number = 0;
	is_neg = 0;
	while (ft_is_space(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg = 1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		number = (number * 10) + nptr[i] - '0';
		i++;
	}
	if (is_neg)
		number = -number;
	return (number);
}

bool	int_check(const char *str)
{
	size_t	i;
	bool	is_neg;
	size_t	num;

	i = 0;
	is_neg = false;
	num = 0;
	if (!str || str[i] == '\0')
		return (false);
	is_neg = (str[i] == '-');
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		if ((!is_neg && num > INT_MAX) || (is_neg && num > 2147483648))
			return (false);
		i++;
	}
	return (true);
}
