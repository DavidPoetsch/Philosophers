/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/01/10 10:04:10 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	eat(t_philo_handler *ph, t_philo *philo)
{
	int	res;

	res = SIM_RUNING;
	sem_wait(ph->sem_forks.sem);
	print_philo_state(ph, philo, PHILO_HAS_TAKEN_FORK);
	sem_wait(ph->sem_forks.sem);
	print_philo_state(ph, philo, PHILO_HAS_TAKEN_FORK);
	print_philo_state(ph, philo, PHILO_IS_EATING);
	update_last_meal_time(philo);
	res = philo_usleep(philo, ph->time_to_eat);
	// usleep(ms_to_us(ph->time_to_eat));
	sem_post(ph->sem_forks.sem);
	sem_post(ph->sem_forks.sem);
	update_meals_eaten(philo);
	return (res);
}

int	go_sleep(t_philo_handler *ph, t_philo *philo)
{
	int	res;

	res = SIM_RUNING;
	print_philo_state(ph, philo, PHILO_IS_SLEEPING);
	res = philo_usleep(philo, ph->time_to_sleep);
	// usleep(ms_to_us(ph->time_to_eat));
	return (res);
}

void	think(t_philo_handler *ph, t_philo *philo)
{
	print_philo_state(ph, philo, PHILO_IS_THINKING);
	// usleep(ms_to_us(3));
}

static void	send_finished(t_philo_handler *ph)
{
	sem_post(ph->sem_philo_finished.sem);
	// post philo_handler sem_philo_finished
}

static int	check_sim_running(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;
	int	meals;

	if (ph->meal_limit)
	{
		get_int_sem(&philo->sem_meals, &meals);
		if (meals >= ph->meals_per_philo)
			return (SIM_FINISHED);
	}
	get_int_sem(&philo->sem_sim_state, &sim_state);
	if (sim_state == SIM_FINISHED)
		return (SIM_FINISHED);
	return (SIM_RUNING);
}

static void	*t_philo_life(void *p)
{
	int				res;
	t_philo			*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	print_philo_state(ph, philo, PHILO_IS_THINKING);
	while (check_sim_running(ph, philo) == SIM_RUNING)
	{
		res = eat(ph, philo);
		if (res == SIM_RUNING)
			res = go_sleep(ph, philo);
		if (res == SIM_RUNING)
			think(ph, philo);
	}
	send_finished(ph);
	return (NULL);
}

void	philo_life(void *p)
{
	t_philo	*philo;
	int		res;

	if (!p)
		return ;
	philo = (t_philo *)p;
	res = t_create(&philo->t_mon_sim_state, t_mon_sim_state, philo);
	if (res != ERROR)
		res = t_create(&philo->t_mon_death, t_mon_philo_death, philo);
	if (res != ERROR)
		res = t_create(&philo->t_philo_life, t_philo_life, philo);
	if (philo->t_mon_sim_state.state == STATE_THREAD_CREATED)
		t_join(&philo->t_mon_sim_state);
	if (philo->t_mon_death.state == STATE_THREAD_CREATED)
		t_join(&philo->t_mon_death);
	if (philo->t_philo_life.state == STATE_THREAD_CREATED)
		t_join(&philo->t_philo_life);
	if (res == ERROR)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
