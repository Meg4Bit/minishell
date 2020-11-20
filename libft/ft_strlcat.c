/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:44:53 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/07 22:05:49 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		j;
	size_t	dist;

	i = ft_strlen(dst);
	j = 0;
	dist = i;
	while (j < (int)(size - 1 - dist) && src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
	if (dist > size)
		dist = size;
	return (dist + ft_strlen(src));
}
