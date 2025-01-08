/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/08 17:08:16 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int eat(t_philo_handler	*ph, t_philo	*philo)
{
	int res;

	res = SIM_RUNING;
	sem_wait(ph->sem_forks.sem);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	sem_wait(ph->sem_forks.sem);
	print_philo_state(ph, philo->id, PHILO_HAS_TAKEN_FORK);
	print_philo_state(ph, philo->id, PHILO_IS_EATING);
	// update_last_meal_time(philo);
	// res = philo_usleep(ph, ph->time_to_eat);
	usleep(ms_to_us(ph->time_to_eat));
	sem_post(ph->sem_forks.sem);
	sem_post(ph->sem_forks.sem);
	philo->meals++;
	return (res);
}

int go_sleep(t_philo_handler	*ph, t_philo	*philo)
{
	int res;

	res = SIM_RUNING;
	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	// res = philo_usleep(ph, ph->time_to_sleep);
	usleep(ms_to_us(ph->time_to_eat));
	return (res);
}

void	think(t_philo_handler	*ph, t_philo	*philo)
{
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	usleep(ms_to_us(20));
}

static void	send_finished(t_philo_handler	*ph)
{
	sem_post(ph->sem_sim_state.sem);
	// post philo_handler sem_philo_finished
}

static int	check_sim_running(t_philo_handler	*ph, t_philo	*philo)
{
	int sim_state;

	sim_state = SIM_RUNING;
	if (philo->meals >= ph->meals_per_philo)
		return(SIM_FINISHED);
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_FINISHED)
		return(SIM_FINISHED);
	return (SIM_RUNING);
}

void	philo_life(void *p)
{
	int res;
	t_philo	*philo;
	t_philo_handler	*ph;

	if (!p)
		return ;
	philo = (t_philo *)p;
	ph = philo->ph;
	start_philo_mon_thread(philo); // todo handl error
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	while(check_sim_running(ph, philo))
	{
		res = eat(ph, philo);
		if (res == SIM_RUNING)
			res = go_sleep(ph, philo);
		if (res == SIM_RUNING)
			think(ph, philo);
	}
	send_finished(ph);
	pthread_join(philo->ptid_mon_sim_state, NULL);// wait for local monitoring thread
	exit(EXIT_SUCCESS);
}
