/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/16 17:44:43 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int think(t_philo_handler	*ph, t_philo	*philo)
{
	int result;

	result = EATING_DENIED;
	pthread_mutex_lock(&ph->lock);
	ph->last_lock_id = philo->id;
	if (ph->philos == 1)
		result = EATING_ALLOWED;
	else if (philo->fork1->state == FORK_AVAILABLE && philo->fork2->state == FORK_AVAILABLE)
	{
		philo->fork1->state = FORK_UNAVAILABLE;
		philo->fork2->state = FORK_UNAVAILABLE;
		result = EATING_ALLOWED;
	}
	pthread_mutex_unlock(&ph->lock);
	return (result);
}

void eat(t_philo_handler	*ph, t_philo	*philo)
{
	pthread_mutex_lock(&philo->fork1->lock);
	if (ph->philos > 1)
		pthread_mutex_lock(&philo->fork2->lock);
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	usleep(ms_to_us(ph->time_to_eat));
	philo->fork1->state = FORK_AVAILABLE;
	philo->fork2->state = FORK_AVAILABLE;
	pthread_mutex_unlock(&philo->fork1->lock);
		if (ph->philos > 1)
	pthread_mutex_unlock(&philo->fork2->lock);
	philo->meals++;
}

void go_sleep(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	usleep(ms_to_us(ph->time_to_sleep));
}

void	*philo_life(void *p)
{
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	while(philo->meals < ph->meals_per_philo)
	{
		if (think(ph, philo) == EATING_ALLOWED)
		{
			eat(ph, philo);
			go_sleep(ph, philo);
			print_philo_state(ph, philo->id, PHILO_IS_THINKING);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_handler	ph;
	int				i;

	init_args(&args, argc, argv);
	if (init_philos(args, &ph) == ERROR)
		return (EXIT_FAILURE);
	i = 0;
	while (i < ph.philos)
	{
		pthread_create(&ph.philo_lst[i].ptid, NULL, philo_life, &ph.philo_lst[i]);
		i++;
	}
	i = 0;
	while (i < ph.philos)
	{
		pthread_join(ph.philo_lst[i].ptid, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}


// static pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
// static pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

// void *test(void *p)
// {
// 	int res1;
// 	int res2;
// 	int *id;

// 	if (!p)
// 		return NULL;
// 	id = (int*)p;
// 	res1 = pthread_mutex_lock(&m1);
// 	printf("%d: res1 = %d\n", *id, res1);
// 	res2 = pthread_mutex_lock(&m2);
// 	printf("%d: res2 = %d\n", *id, res2);
// 	usleep(1000000);
// 	pthread_mutex_unlock(&m1);
// 	pthread_mutex_unlock(&m2);
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_t t1 = 0;
// 	pthread_t t2 = 0;
// 	int id1 = 1;
// 	int id2 = 2;

// 	pthread_mutex_init(&m1, NULL);
// 	pthread_mutex_init(&m2, NULL);
// 	pthread_create(&t1, NULL, &test, &id1);
// 	pthread_create(&t2, NULL, &test, &id2);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	return (EXIT_SUCCESS);
// }