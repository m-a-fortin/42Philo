/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:34:28 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/14 12:37:22 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

bool	ph_wait(t_args *data, long time_to, t_table *philo)
{
	unsigned long	now;

	now = ph_get_time();
	while ((ph_get_time() - now) < (unsigned long)time_to)
	{
		if ((ph_starvation(philo, data) == true || data->game_over == true)
			&& (philo->state != EAT))
			return (false);
	}
	return (true);
}

bool	ph_print_state(t_args *data, char *string, t_table *philo)
{
	unsigned long	current_time;
	unsigned long	diff;

	(void)string;
	if (ph_starvation(philo, data) == true || data->game_over == true)
		return (false);
	pthread_mutex_lock(&data->m_write);
	current_time = ph_get_time();
	if (current_time == 0)
		return (false);
	diff = current_time - data->time_save;
	if (data->game_over == false)
		printf("%lu %d %s\n", diff, philo->id + 1, string);
	pthread_mutex_unlock(&data->m_write);
	if (ph_starvation(philo, data) == true || data->game_over == true)
		return (false);
	return (true);
}

bool	ph_starvation(t_table *philo, t_args *data)
{
	unsigned long	current;
	unsigned long	check;

	if (philo->state == EAT)
		return (false);
	current = ph_get_time();
	check = current - philo->starving;
	pthread_mutex_lock(&data->m_write);
	if (check > data->time.r_die && data->game_over == false)
	{
		data->game_over = true;
		printf("%lu %d died\n", check, philo->id + 1);
		pthread_mutex_unlock(&data->m_write);
		pthread_mutex_lock(&philo->m_fork);
		return (true);
	}
	pthread_mutex_unlock(&data->m_write);
	return (false);
}

bool	ph_join(t_args *data)
{
	int	index;

	index = 0;
	while (index < data->nb_philo)
	{
		if (pthread_join(data->philo[index].th, NULL) != 0)
			return (false);
		index++;
	}
	return (true);
}

void	ph_first_turn(t_args *data, t_table *philo)
{
	data->time_save = ph_get_time();
	philo->starving = ph_get_time();
}
