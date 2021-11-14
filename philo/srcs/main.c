/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:51:49 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/14 12:35:59 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

void	ph_solo(t_table *philo, t_args *data)
{
	data->time_save = ph_get_time();
	philo->starving = ph_get_time();
	ph_print_state(data, "has taken a fork", philo);
	while (true)
	{
		if (ph_starvation(philo, data) == true || data->game_over == true)
			return ;
	}
}

unsigned long	ph_get_time(void)
{
	struct timeval	time;
	unsigned long	now;

	if (gettimeofday(&time, NULL) == -1)
	{
		perror("philo:");
		return (0);
	}
	now = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now);
}

int	ph_free(t_args *data)
{
	free(data->queue);
	free(data->philo);
	free(data);
	return (1);
}

int	ph_exit(t_args *data)
{
	int	index;
	int	ret;

	index = 0;
	ret = 0;
	ret += pthread_mutex_destroy(&data->m_dead);
	ret += pthread_mutex_destroy(&data->m_write);
	ret += pthread_mutex_destroy(&data->m_meal);
	if (ret != 0)
	{
		ft_putendl_fd("philo: mutex error", 2);
		return (ph_free(data));
	}
	while (index < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->philo[index].m_fork) != 0)
			return (ph_free(data));
		index++;
	}
	ph_free(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	*data;

	data = malloc(sizeof(t_args));
	if (!data)
		return (1);
	data->b_meal = false;
	data->game_over = false;
	if (ph_parsing_args(argc, argv, data) == false)
	{
		free(data);
		return (127);
	}
	data->nb_done = data->nb_philo;
	if (ph_init_main(data) == false)
	{
		free(data);
		return (1);
	}
	if (ph_exec_main(data) == false)
		return (ph_free(data));
	return (ph_exit(data));
}
