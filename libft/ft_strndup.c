/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 20:27:06 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/08 02:43:31 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s, int n)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen(s);
	if ((n > len))
		n = len;
	if (!(ptr = malloc(sizeof(char) * (n + 1))))
		return (0);
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
