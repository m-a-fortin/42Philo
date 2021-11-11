/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_activity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:51:46 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/11 14:29:29 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool	ph_sleep(t_table *philo, t_args *data)
{
	if (ph_starvation(philo, data) == true || data->game_over == true)
		return (false);
	philo->state = SLEEP;
	if (ph_print_state(data, "is sleeping", philo) == false)
		return (false);
	if (ph_wait(data, data->time.r_sleep, philo) == false)
		return (false);
	philo->state = THINK;
	if (ph_print_state(data, "is thinking", philo) == false)
		return (false);
	return (true);
}

bool	ph_take_forks(t_table *philo, t_table *next_philo, t_args *data)
{
	while (true)
	{
		if (philo->b_fork == true && next_philo->b_fork == true)
		{
			if (ph_starvation(philo, data) == true || data->game_over == true)
				return (false);
			pthread_mutex_lock(&philo->m_fork);
			philo->b_fork = false;
			pthread_mutex_unlock(&philo->m_fork);
			ph_print_state(data, "has taken a fork", philo);
			pthread_mutex_lock(&next_philo->m_fork);
			next_philo->b_fork = false;
			pthread_mutex_unlock(&next_philo->m_fork);
			ph_print_state(data, "has taken a fork", philo);
			if (ph_starvation(philo, data) == true || data->game_over == true)
				return (false);
			return (true);
		}
		if (ph_starvation(philo, data) == true)
			return (false);
	}
	return (false);
}

bool	ph_eat(t_table *philo, t_table *next_philo, t_args *data)
{
	philo->starving = ph_get_time();
	philo->state = EAT;
	if (ph_print_state(data, "is eating", philo) == false)
		return (false);
	ph_wait(data, data->time.r_eat, philo);
	pthread_mutex_lock(&philo->m_fork);
	philo->b_fork = true;
	pthread_mutex_unlock(&philo->m_fork);
	pthread_mutex_lock(&next_philo->m_fork);
	next_philo->b_fork = true;
	pthread_mutex_unlock(&next_philo->m_fork);
	if (data->b_meal == true)
	{
		philo->nb_meal--;
		if (philo->nb_meal == 0)
			data->nb_done--;
		if (data->nb_done == 0)
		{
			data->game_over = true;
			return (false);
		}
	}
	return (true);
}
