/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:11:14 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/13 11:19:38 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
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
