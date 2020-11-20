/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 01:13:38 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/08 15:17:16 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	pos;
	size_t	little_len;
	char	*occ;

	occ = (char *)big;
	if (!(little_len = ft_strlen(little)))
		return (occ);
	pos = 0;
	while (occ[pos] && pos < len)
	{
		i = 0;
		while (little[i] && occ[pos + i] == little[i] &&\
				(pos + i) < len)
			i++;
		if (i == little_len)
			return (occ + pos);
		pos++;
	}
	return (0);
}
