/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:30:47 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:11:52 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int init_sem_philo_handler(t_philo_handler *ph)
{
	int res;

	ph->sem_print.free_name = false;
	ph->sem_forks.free_name = false;
	ph->sem_sim_state.free_name = false;
	ph->sem_print.name = SEM_NAME_PRINT;
	ph->sem_forks.name = SEM_NAME_FORKS;
	ph->sem_sim_state.name = SEM_NAME_SIM_STATE;
	res = init_semaphore(&ph->sem_forks, ph->philos);
	if (res != ERROR)
		res = init_semaphore(&ph->sem_print, 1);
	if (res != ERROR)
		res = init_semaphore(&ph->sem_sim_state, 0);
	return (res);
}

static int create_sem_name(t_sem *sem, const char *prefix, int id)
{
	char *char_id;

	sem->name = NULL;
	sem->free_name = false;
	char_id = ft_itoa(id);
	if (char_id == NULL)
	{
		ft_puterr(ERR_CREATE_SEM_NAME);
		return (ERROR);
	}
	sem->name = ft_strjoin(prefix, char_id);
	free(char_id);
	if (sem->name == NULL)
	{
		ft_puterr(ERR_CREATE_SEM_NAME);
		return (ERROR);
	}
	char_id = NULL;
	sem->free_name = true;
	return (SUCCESS);
}

static int init_sem_philos(t_philo_handler *ph)
{
	int i;
	int res;
	char *sem_name;
	t_philo *philo;

	i = 0;
	sem_name = NULL;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		res = create_sem_name(&philo->sem_meals.sem, SEM_NAME_MEALS, i);
		if (res != ERROR)
			res = init_semaphore(&philo->sem_meals.sem, 1);
		if (res != ERROR)
			res = create_sem_name(&philo->sem_tv_last_meal.sem, SEM_NAME_LAST_MEAL, i);
		if (res != ERROR)
			res = init_semaphore(&philo->sem_tv_last_meal.sem, 1);
		if (res != ERROR)
			res = create_sem_name(&philo->sem_sim_state.sem, SEM_NAME_LAST_MEAL, i);
		if (res != ERROR)
			res = init_semaphore(&philo->sem_sim_state.sem, 0);
		if (res == ERROR)
			return (res);
		i++;
	}
	return (res);
}

int init_semaphores(t_philo_handler *ph)
{
	int res;

	res = init_sem_philo_handler(ph);
	if (res != ERROR)
		res = init_sem_philos(ph);
	return (res);
}
