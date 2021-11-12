/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:53:06 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/12 17:03:52 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

bool	ph_init_loop(t_args *data)
{
	t_table	*philo;
	int		index;
	int		m_ret;

	index = 0;
	philo = data->philo;
	while (index < data->nb_philo)
	{
		philo[index].id = index;
		philo[index].state = THINK;
		philo[index].b_fork = true;
		philo[index].data = data;
		if (data->b_meal == true)
			philo[index].nb_meal = data->nb_meal;
		m_ret = pthread_mutex_init(&philo[index].m_fork, NULL);
		if (m_ret != 0)
		{
			ft_putstr_fd("philo: fatal: mutex error\n", 2);
			free(data->philo);
			free(data->queue);
			return (false);
		}
		index++;
	}
	return (true);
}

bool	ph_init_queue(t_args *data)
{
	int	i;
	int	index;

	data->queue = malloc(sizeof(int) * data->nb_philo);
	if (!data->queue)
		return (false);
	i = 0;
	index = 0;
	while (index < data->nb_philo)
	{
		data->queue[i] = index;
		index += 2;
		i++;
	}
	index = 1;
	while (index < data->nb_philo)
	{
		data->queue[i] = index;
		index += 2;
		i++;
	}
	return (true);
}

bool	ph_init_main(t_args *data)
{
	int		m_ret;

	m_ret = 0;
	data->philo = malloc(sizeof(t_table) * data->nb_philo);
	if (!data->philo)
		return (false);
	m_ret += pthread_mutex_init(&data->m_write, NULL);
	m_ret += pthread_mutex_init(&data->m_dead, NULL);
	m_ret += pthread_mutex_init(&data->m_meal, NULL);
	if (m_ret != 0)
	{
		ft_putstr_fd("philo: fatal: mutex error\n", 2);
		free(data->philo);
		return (false);
	}
	if (ph_init_queue(data) == false)
	{
		free(data->philo);
		return (false);
	}
	return (ph_init_loop(data));
}

bool	ph_parsing_args(int argc, char **argv, t_args *data)
{
	if (argc != 5 && argc != 6)
		return (ph_parsing_error('#'));
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo <= 0)
		return (ph_parsing_error('+'));
	data->time.r_die = ft_atoi(argv[2]);
	if (data->time.r_die <= 0)
		return (ph_parsing_error('+'));
	data->time.r_eat = ft_atoi(argv[3]);
	if (data->time.r_eat <= 0)
		return (ph_parsing_error('+'));
	data->time.r_sleep = ft_atoi(argv[4]);
	if (data->time.r_sleep <= 0)
		return (ph_parsing_error('+'));
	if (argc == 6)
	{
		data->nb_meal = ft_atoi(argv[5]);
		data->b_meal = true;
		if (data->nb_meal <= 0)
			return (ph_parsing_error('+'));
	}
	return (true);
}
