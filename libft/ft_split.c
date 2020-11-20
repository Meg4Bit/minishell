/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:04:17 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/11 15:40:06 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arr_len(char const *s, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s != c)
			count++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static char	*sep_str(char const *s, char c)
{
	int		len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (ft_substr(s, 0, len));
}

static void	*free_arr(char **arr)
{
	if (arr)
	{
		while (*arr)
			free(*arr++);
		free(arr);
	}
	return (0);
}

char		**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		len;

	i = 0;
	len = arr_len(s, c);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (arr)
	{
		while (i < len)
		{
			while (*s == c && *s)
				s++;
			arr[i] = sep_str(s, c);
			if (!arr[i])
				return (free_arr(arr));
			while (*s != c && *s)
				s++;
			i++;
		}
		arr[i] = NULL;
		return (arr);
	}
	return (0);
}
