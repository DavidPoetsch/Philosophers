/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 09:32:38 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/09 09:20:36 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static char	*ft_strcat(char *dest, char const *src);

/**
 * @brief Allocates (with malloc(3)) and returns a new string,
*					which is the result of the concatenation of ’s1’ and ’s2’.
 * @param s1	The prefix string.
 * @param s2	The suffix string.
 * @return char*	Combined string.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	strlen;

	strlen = 0;
	strlen += ft_strlen(s1);
	strlen += ft_strlen(s2);
	str = (char *)malloc((strlen + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	if (strlen <= 0)
		return (str);
	ft_strcat(str, s1);
	ft_strcat(str, s2);
	return (str);
}

static char	*ft_strcat(char *dest, char const *src)
{
	size_t	len_dest;
	size_t	i;

	len_dest = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (dest);
}

/*
int	main(int argc, char **argv)
{
	char const	*s1;
	char const	*s2;
	char		*dest;

	s1 = "Hello";
	s2 = "World";
	dest = ft_strjoin(s1, s2);
	printf("result = '%s'\n", dest);
	printf("dest len = %zu\n", ft_strlen((char const *)dest));
	if(dest != NULL)
		free(dest);
}
 */