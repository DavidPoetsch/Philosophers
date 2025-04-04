/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotsch <poetschdavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:06:34 by dpotsch           #+#    #+#             */
/*   Updated: 2025/04/04 10:30:08 by dpotsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/**
 * @brief ### Take forks
 *
 * - Take fork 1
 *
 * - Take fork 2
 *
 * @param ph philo handler
 * @param philo philo
 * @return int sim state
 */
int	take_forks(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	sim_state = SIM_FINISHED;
	lock_mutex(philo->fork1);
	philo->fork_state = PHILO_TOOK_FORK1;
	get_int_mutex(&ph->m_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		print_philo_state_fork(ph, philo, 1);
		if (ph->philos == 1)
		{
			while (sim_state == SIM_RUNING)
			{
				get_int_mutex(&ph->m_sim_state, &sim_state);
				usleep(MON_PAUSE);
			}
			return (sim_state);
		}
		lock_mutex(philo->fork2);
		philo->fork_state = PHILO_TOOK_FORK2;
		get_int_mutex(&ph->m_sim_state, &sim_state);
		if (sim_state == SIM_RUNING)
			print_philo_state_fork(ph, philo, 2);
	}
	return (sim_state);
}

/**
 * @brief ### Eat
 *
 * - update last meal time.
 *
 * - eat for x time.
 *
 * - put forks down.
 *
 * - update meal count.
 *
 * @param ph philo handler
 * @param philo philo
 * @return int sim state
 */
int	eat(t_philo_handler *ph, t_philo *philo)
{
	unsigned long long	us_curr;
	int					sim_state;

	sim_state = SIM_FINISHED;
	get_int_mutex(&ph->m_sim_state, &sim_state);
	if (sim_state == SIM_RUNING)
	{
		us_curr = print_philo_state(ph, philo->id, PHILO_IS_EATING);
		update_time_to_die(philo, us_curr);
		sim_state = philo_usleep(ph, philo->time_to_eat);
		inc_int_mutex(&philo->m_meals);
	}
	return (sim_state);
}

/**
 * @brief ### Sleep
 *
 * - After eat philo sleeps for x time.
 *
 * @param ph philo handler
 * @param philo philo
 * @return int sim state
 */
int	go_sleep(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	print_philo_state(ph, philo->id, PHILO_IS_SLEEPING);
	sim_state = philo_usleep(ph, philo->time_to_sleep);
	return (sim_state);
}

/**
 * @brief ### Think
 *
 * - After sleep, philo is thinking.
 *
 * Delay needed for odd number of philos.
 * The delay is necessary for fair fork access.
 *
 * @param ph philo handler
 * @param philo philo
 */
int	think(t_philo_handler *ph, t_philo *philo)
{
	int	sim_state;

	sim_state = SIM_RUNING;
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	if (ph->philos % 2 != 0)
		sim_state = philo_usleep(ph, philo->time_to_think);
	return (sim_state);
}

/**
 * @brief ### Life of a philosopher (EAT - SLEEP - THINK - REPEAT).
 */
void	*philo_life(void *p)
{
	int				sim_state;
	t_philo			*philo;
	t_philo_handler	*ph;

	if (!p)
		return (NULL);
	philo = (t_philo *)p;
	ph = philo->ph;
	update_time_to_die(philo, get_curr_us());
	print_philo_state(ph, philo->id, PHILO_IS_THINKING);
	while (sim_running(ph, philo))
	{
		sim_state = take_forks(ph, philo);
		if (sim_state == SIM_RUNING)
			sim_state = eat(ph, philo);
		put_forks_down(philo);
		if (sim_state == SIM_RUNING)
			sim_state = go_sleep(ph, philo);
		if (sim_state == SIM_RUNING)
			sim_state = think(ph, philo);
	}
	return (NULL);
}
