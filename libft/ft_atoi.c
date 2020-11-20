/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:09:20 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/08 15:32:11 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	nb;
	int		minus;

	minus = 1;
	nb = 0;
	while (*str == '\n' || *str == ' ' || *str == '\t' \
			|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb *= 10;
		nb += ((*str++ - 48) * minus);
		if (nb > 2147483647)
			return (-1);
		else if (nb < -2147483648)
			return (0);
	}
	return ((int)nb);
}
