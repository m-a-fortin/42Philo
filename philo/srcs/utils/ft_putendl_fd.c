/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:17:16 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/07 12:38:53 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	char	n;

	n = '\n';
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, &n, 1);
}
