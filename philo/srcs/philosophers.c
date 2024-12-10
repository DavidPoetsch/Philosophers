/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/06 13:02:18 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

typedef struct s_philo
{
	int thread_id;
	char *message;
} t_philo;

void 	*hello_fun(void *p)
{
	if (!p)
		return (NULL);
	t_philo *philo = (t_philo *)p;
	printf("%d: %s\n", philo->thread_id, philo->message);
	return (NULL);
}

int main (void)
{

	t_philo p1;

	p1.thread_id = 10;
	p1.message = "TEST";

	pthread_t thread = NULL;
	pthread_create(&thread, NULL, hello_fun, &p1);
	pthread_join(thread, NULL);
	return (EXIT_SUCCESS);
}
