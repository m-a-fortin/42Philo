/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:52:01 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/07 12:42:27 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdbool.h>
#include <stdio.h>

bool	ph_parsing_error(char type)
{
	if (type == '#')
	{
		ft_putstr_fd("error\ninvalid nb of arguments:", 2);
		ft_putendl_fd(" check README for correct usage", 2);
	}
	else if (type == '+')
	{
		ft_putstr_fd("error\nvalue in arguments higher", 2);
		ft_putendl_fd(" than INT_MAX or smaller than 1", 2);
	}
	return (false);
}

bool	ph_perror(void)
{
	perror("philo:");
	return (false);
}
