/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:07:09 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/17 17:07:37 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_philo_threads(t_philo_handler	*ph)
{
	int i;

	i = 0;
	while (i < ph->philos)
	{
		pthread_create(&ph->philo_lst[i].ptid, NULL, philo_life, &ph->philo_lst[i]);
		i++;
	}
	return (SUCCESS);
}

int	join_philo_threads(t_philo_handler	*ph)
{
	int i;

	i = 0;
	while (i < ph->philos)
	{
		pthread_join(ph->philo_lst[i].ptid, NULL);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_philo_handler	ph;

	init_args(&args, argc, argv);
	if (init_philos(args, &ph) == ERROR)
		return (EXIT_FAILURE);
	ph.sim_state = SIM_RUNING;
	start_monitoring_thread(&ph);
	start_philo_threads(&ph);
	join_philo_threads(&ph);
	pthread_join(ph.ptid_mon, NULL);
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