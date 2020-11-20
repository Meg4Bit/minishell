/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:04:40 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/09 12:46:23 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		minus;
	char	num;

	if (n == 0)
		write(fd, "0", 1);
	else
	{
		len = 1;
		minus = 1;
		if (n < 0)
			write(fd, "-", 1);
		if (n < 0)
			minus = -1;
		while (n / len > 9 || n / len < -9)
			len *= 10;
		while (len)
		{
			num = ((n / len) * minus + '0');
			write(fd, &num, 1);
			n %= len;
			len /= 10;
		}
	}
}
