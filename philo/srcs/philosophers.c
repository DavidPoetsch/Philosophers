/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/12 17:03:22 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void 	*eat(void *p)
{
	if (!p)
		return (NULL);
	t_philo *philo = (t_philo *)p;
	pthread_mutex_lock(philo->fork);
	int i = 0;
	while (i < 2)
	{
		printf("%d\n", *philo->value);
		sleep(1);
		i++;
		(*philo->value)++;
	}
	printf("Philo %d: %s: finished\n", philo->id, philo->name);
	pthread_mutex_unlock(philo->fork);
	return (NULL);
}

int main (void)
{
	t_philo p1;
	t_philo p2;
	pthread_mutex_t lock;
	int value;

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		ft_puterr("Mutex initialization failed.\n");
		return EXIT_FAILURE;
	}
	p1.fork = &lock;
	p2.fork = &lock;

	p1.value = &value;
	p2.value = &value;

	print_philo_state(1, PHILO_STATE_UNDEFINED);
	print_philo_state(1, PHILO_HAS_TAKEN_FORK);
	print_philo_state(1, PHILO_IS_EATING);
	print_philo_state(1, PHILO_IS_SLEEPING);
	print_philo_state(1, PHILO_IS_THINKING);
	print_philo_state(1, PHILO_DIED);

	p1.id = 1;
	p1.name = "Lukas";
	p2.id = 2;
	p2.name = "David";

	pthread_t thread1 = 0;
	pthread_t thread2 = 0;
	pthread_create(&thread1, NULL, eat, &p1);
	pthread_create(&thread2, NULL, eat, &p2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (EXIT_SUCCESS);
}
