/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:09:52 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 14:31:55 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
static int	ft_is_space(char c);
static int	ft_isdigit(int c);

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

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_is_space(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}
