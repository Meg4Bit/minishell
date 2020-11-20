/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 14:30:35 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/07 22:52:28 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*lastd;
	const char	*lasts;

	if (!dest && !src)
		return (0);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		lasts = (const char *)src + (n - 1);
		lastd = (char *)dest + (n - 1);
		while (n--)
			*lastd-- = *lasts--;
	}
	return (dest);
}
