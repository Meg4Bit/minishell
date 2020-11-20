/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:25:23 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/08 19:54:16 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		len;

	if (!s1)
		return (0);
	i = 0;
	start = 0;
	len = ft_strlen(s1) - 1;
	while (set[i] && start <= len)
	{
		if (set[i] == s1[start] || set[i] == s1[len])
		{
			if (set[i] == s1[start])
				start++;
			if (set[i] == s1[len])
				len--;
			i = 0;
		}
		else
			i++;
	}
	return ((len = len - start + 1) >= 0 ?\
			ft_substr(s1, start, len) : ft_substr(s1, start, 0));
}
