/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:30:47 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/01 17:17:32 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_sem_philo_handler(t_philo_handler *ph)
{
	int	res;

	res = init_semaphore(&ph->sem_forks, SEM_NAME_FORKS, ph->philos);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_forks_request, SEM_NAME_FORKS_REQ, 1);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_print, SEM_NAME_PRINT, 1);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_philo_finished, SEM_NAME_PHILO_FIN, 0);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_stop_simulation, SEM_NAME_STOP_SIM, 0);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_stop_feedback, SEM_NAME_STOP_FB, 0);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_error, SEM_NAME_ERROR, 0);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_philos_started, SEM_NAME_PHILO_START, 0);
	if (res == SUCCESS)
		res = init_semaphore(&ph->sem_death, SEM_NAME_DEATH, 1);
	return (res);
}

static int	create_sem_name(t_sem *sem, const char *prefix, int id)
{
	char	*char_id;

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

static int	create_sem_names(t_philo_handler *ph)
{
	int		i;
	int		res;
	t_philo	*philo;
	t_sem	*sem;

	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		sem = &philo->sem_time_of_death.sem;
		res = create_sem_name(sem, SEM_NAME_TIME_OF_DEATH, i);
		if (res != ERROR)
		{
			sem = &philo->sem_sim_state.sem;
			res = create_sem_name(sem, SEM_NAME_SIM_STATE, i);
		}
		if (res == ERROR)
			return (res);
		i++;
	}
	return (res);
}

static int	init_sem_philos(t_philo_handler *ph)
{
	int		i;
	int		res;
	t_philo	*philo;

	create_sem_names(ph);
	i = 0;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		res = init_semaphore(&philo->sem_time_of_death.sem, NULL, 1);
		if (res != ERROR)
			res = init_semaphore(&philo->sem_sim_state.sem, NULL, 1);
		philo->sem_sim_state.value = SIM_RUNING;
		if (res == ERROR)
			return (res);
		i++;
	}
	return (res);
}

int	init_semaphores(t_philo_handler *ph)
{
	int	res;

	res = init_sem_philo_handler(ph);
	if (res != ERROR)
		res = init_sem_philos(ph);
	return (res);
}
