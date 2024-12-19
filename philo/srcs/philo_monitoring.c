/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2024/12/19 15:57:23 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int check_philo_death(t_philo_handler *ph, t_philo *philo, t_tv	*tv_curr)
{
	int	ms;
	t_tv tv_last_meal;

	get_tv_mutex(&philo->m_tv_last_meal, &tv_last_meal);
	ms = get_time_duration_in_ms(tv_last_meal, *tv_curr);
	if (ms >= ph->time_to_die)
	{
		// printf("dead: %ld, %ld \n", philo->m_tv_last_meal.tv.tv_sec, philo->m_tv_last_meal.tv.tv_usec);
		// printf("dead: %ld, %ld \n", tv_curr->tv_sec, tv_curr->tv_usec);
		print_philo_state(ph, philo->id, PHILO_IS_DEAD);
		return (SIM_FINISHED);
	}
	return (SIM_RUNING);
}

int	philo_meals_finished(t_philo_handler *ph, t_philo *philo, int *philo_meals_total)
{
	int philo_meals;

	if (ph->meal_limit == false)
		return (SIM_RUNING);
	philo_meals = 0;
	get_int_mutex(&philo->m_meals, &philo_meals);
	(*philo_meals_total) -= philo_meals;
	if (*philo_meals_total <= 0)
		return (SIM_FINISHED);
	return (SIM_RUNING);
}

static int	check_philos_state(t_philo_handler *ph)
{
	int	i;
	t_philo *philo;
	t_tv	tv_curr;
	int sim_state;
	int philo_meals_total;

	if (get_current_time(&tv_curr) == ERROR)
		return (SIM_FINISHED);
	i = 0;
	philo_meals_total = ph->meals_per_philo * ph->philos;
	while (i < ph->philos)
	{
		philo = &ph->philo_lst[i];
		sim_state = philo_meals_finished(ph, philo, &philo_meals_total);
		if (sim_state != SIM_FINISHED)
			sim_state = check_philo_death(ph, philo, &tv_curr);
		if (sim_state == SIM_FINISHED)
			break;
		i++;
	}
	return (sim_state);
}

void	*philo_monitoring(void *p)
{
	int				sim_state;
	t_philo_handler	*ph;

	if (!p)
		return NULL;
	ph = (t_philo_handler *)p;
	while (1)
	{
		sim_state = check_philos_state(ph);
		if (sim_state == SIM_FINISHED)
		{
			set_int_mutex(&ph->m_sim_state, sim_state);
			break;
		}
		usleep(ms_to_us(5));
	}
	return NULL;
}

int	start_monitoring_thread(t_philo_handler *ph)
{
	pthread_create(&ph->ptid_mon, NULL, philo_monitoring, ph);
	return (SUCCESS);
}
