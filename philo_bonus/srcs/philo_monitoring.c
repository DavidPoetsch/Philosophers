/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:10:26 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:08:51 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void*	check_sim_state(void *p)
{
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	sem_wait(ph->sem_sim_state.sem); //signal from philo_handler (philo has to post philo times on finish)
	set_int_sem(&philo->sem_sim_state, SIM_FINISHED);
	printf("PHILO FINISHED %d\n", philo->id); //! delete
	return (NULL);
}

int	start_philo_mon_thread(t_philo *philo)
{
	pthread_create(&philo->ptid_mon_sim_state, NULL, check_sim_state, philo);
	return (SUCCESS);
}














// static int	check_philo_death(t_philo_handler *ph, t_philo *philo,
// 		t_tv *tv_curr, int meals)
// {
// 	int		ms;
// 	t_tv	tv_last_meal;

// 	if (ph->meal_limit && meals >= ph->meals_per_philo)
// 		return (SIM_RUNING);
// 	get_tv_sem(&philo->sem_tv_last_meal, &tv_last_meal);
// 	ms = get_time_duration_in_ms(tv_last_meal, *tv_curr);
// 	if (ms >= ph->time_to_die)
// 	{
// 		print_philo_state(ph, philo->id, PHILO_IS_DEAD);
// 		return (SIM_FINISHED);
// 	}
// 	return (SIM_RUNING);
// }

// int	philo_meals_finished(t_philo_handler *ph, t_philo *philo, int *meals_total,
// 		int *meals)
// {
// 	if (ph->meal_limit == false)
// 		return (SIM_RUNING);
// 	(*meals) = 0;
// 	get_int_sem(&philo->sem_meals, meals);
// 	(*meals_total) -= (*meals);
// 	if (*meals_total <= 0)
// 		return (SIM_FINISHED);
// 	return (SIM_RUNING);
// }

// static int	check_philos_state(t_philo_handler *ph, t_tv tv_curr)
// {
// 	int		i;
// 	t_philo	*philo;
// 	int		sim_state;
// 	int		meals_total;
// 	int		meals;

// 	i = 0;
// 	meals_total = ph->meals_per_philo * ph->philos;
// 	meals = 0;
// 	while (i < ph->philos)
// 	{
// 		philo = &ph->philo_lst[i];
// 		sim_state = philo_meals_finished(ph, philo, &meals_total, &meals);
// 		if (sim_state != SIM_FINISHED)
// 			sim_state = check_philo_death(ph, philo, &tv_curr, meals);
// 		if (sim_state == SIM_FINISHED)
// 			break ;
// 		i++;
// 	}
// 	return (sim_state);
// }

// void	*philo_monitoring(void *p)
// {
// 	int				sim_state;
// 	t_philo_handler	*ph;
// 	t_tv			tv_curr;

// 	if (!p)
// 		return (NULL);
// 	ph = (t_philo_handler *)p;
// 	while (1)
// 	{
// 		sim_state = SIM_RUNING;
// 		if (get_current_time(&tv_curr) == ERROR)
// 			sim_state = SIM_FINISHED;
// 		if (sim_state == SIM_RUNING)
// 			sim_state = check_philos_state(ph, tv_curr);
// 		if (sim_state == SIM_FINISHED)
// 		{
// 			set_int_sem(&ph->sem_sim_state, &sim_state);
// 			break ;
// 		}
// 		usleep(ms_to_us(MS_MON_SLEEP));
// 	}
// 	return (NULL);
// }

// // int	start_monitoring_thread(t_philo_handler *ph)
// // {
// // 	pthread_create(&ph->ptid_mon, NULL, philo_monitoring, ph);
// // 	return (SUCCESS);
// // }
