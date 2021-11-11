/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ulong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:42:48 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/07 12:38:14 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	ft_putnbr_ulong(unsigned long n)
{
	unsigned long	nb;

	nb = n;
	if (nb > 9)
	{
		ft_putnbr_ulong(nb / 10);
		ft_putnbr_ulong(nb % 10);
	}
	else
		ft_putchar_fd(nb + 48, 1);
}
