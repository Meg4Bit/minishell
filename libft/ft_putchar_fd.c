/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 10:58:16 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/09 19:28:52 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	char buf[3];

	if ((unsigned char)c > 127)
	{
		buf[0] = (((unsigned char)c >> 6) & 31) | 192;
		buf[1] = ((unsigned char)c & 63) | 128;
		buf[2] = 0;
		write(fd, buf, 2);
	}
	else
		write(fd, &c, 1);
}
