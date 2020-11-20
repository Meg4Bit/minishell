/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:27:06 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/07 19:58:27 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (new_str)
	{
		i = 0;
		while (s[i])
		{
			new_str[i] = s[i];
			i++;
		}
		new_str[i] = s[i];
	}
	return (new_str);
}
