/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:38:55 by dpotsch           #+#    #+#             */
/*   Updated: 2025/03/14 15:37:05 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr(char *str)
{
	if (!str)
		return (-1);
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

int	ft_puterr(char *str)
{
	if (!str)
		return (-1);
	return (write(STDERR_FILENO, str, ft_strlen(str)));
}

void	ft_putnbr(size_t n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
	}
	c = (n % 10) + '0';
	write(STDOUT_FILENO, &c, 1);
}

void	ft_swap_ptr(void **p1, void **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
