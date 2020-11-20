/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:18:01 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/07 19:48:56 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *first;
	unsigned char *second;

	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (n--)
	{
		if (*first != *second)
			return (*first - *second);
		first++;
		second++;
	}
	return (0);
}
