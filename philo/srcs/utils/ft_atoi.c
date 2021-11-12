/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:14:01 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/12 17:10:35 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_atoi(const char *str)
{
	int		negative;
	long	nb;

	negative = 1;
	nb = 0;
	while ((*str >= '\t' && *str <= '\r') || (*str == ' '))
		str++;
	if (*str == '-')
		return (0);
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + *str - 48;
		str++;
		if (nb * negative > 2147483647)
			return (0);
		if (nb * negative < -2147483648)
			return (0);
	}
	return (nb * negative);
}
