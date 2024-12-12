/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:38:55 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/12 12:39:24 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (i);
	while(str[i])
		i++;
	return (i);
}

int	ft_puterr(char *str)
{
	return (write(STDERR_FILENO, str, ft_strlen(str)));
}
