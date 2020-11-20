/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:09:15 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/08 14:45:42 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (*s)
		s++;
	while (i > 0)
	{
		if (*s == c)
			return ((char *)s);
		i--;
		s--;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
