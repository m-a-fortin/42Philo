/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:52:07 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/11 13:55:17 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	ph_place_last(t_args *data)
{
	int	temp;
	int	index;
	int	total;

	index = 0;
	total = data->nb_philo;
	temp = data->queue[0];
	while (index < total - 1)
	{
		data->queue[index] = data->queue[index + 1];
		index++;
	}
	data->queue[index] = temp;
}

bool	ph_queue(t_args *data, t_table *philo, t_table *next_philo)
{
	(void)next_philo;
	(void)data;
	if (ph_starvation(philo, data) == true || data->game_over == true)
		return (false);
	if (philo->id == data->queue[0])
	{
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return (false);
		if (ph_take_forks(philo, next_philo, data) == false)
			return (false);
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return (false);
		ph_place_last(data);
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return (false);
		if (ph_eat(philo, next_philo, data) == false)
			return (false);
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return (false);
		if (ph_sleep(philo, data) == false)
			return (false);
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return (false);
	}
	return (true);
}

void	ph_routine_loop(t_args *data, t_table *philo, t_table *next_philo)
{
	int	turn;

	turn = 0;
	while (data->game_over == false)
	{
		if (turn == 0)
		{
			data->time_save = ph_get_time();
			philo->starving = ph_get_time();
		}
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return ;
		if (data->nb_philo == 1)
			return (ph_solo(philo, data));
		if (ph_queue(data, philo, next_philo) == false)
			return ;
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return ;
		turn++;
	}
}

void	*ph_routine(void *arg)
{
	t_args	*data;
	t_table	*philo;
	t_table	*next_philo;

	philo = arg;
	data = philo->data;
	if (philo->id == data->nb_philo - 1)
		next_philo = &data->philo[0];
	else
		next_philo = &data->philo[philo->index + 1];
	ph_routine_loop(data, philo, next_philo);
	return (arg);
}

bool	ph_exec_main(t_args *data)
{
	int		ret;
	int		index;
	t_table	*philo;

	philo = data->philo;
	index = 0;
	while (index < data->nb_philo)
	{
		philo[index].index = index;
		ret = pthread_create(&philo[index].th, NULL,
				&ph_routine, &philo[index]);
		if (ret == -1)
		{
			perror("philo:");
			return (false);
		}
		index++;
	}
	return (ph_join(data));
	return (true);
}
