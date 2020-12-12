/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:21:07 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/12 23:49:49 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_mod(char const *s1, char const set)
{
	int		i;
	int		start;
	int		len;

	if (!s1)
		return (0);
	start = 0;
	len = 0;
	while (s1[start] && s1[start] == set)
		start++;
	i = start;
	while (s1[i])
	{
		if (s1[i] != set)
		{
			if (s1[i] == '\\')
				i++;
			len = i;
		}
		i += s1[i] ? 1 : 0;
	}
	return ((len = len - start + 1) >= 0 ?\
			ft_substr(s1, start, len) : ft_substr(s1, start, 0));
}