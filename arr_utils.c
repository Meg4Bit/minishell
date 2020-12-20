/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 18:59:56 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/20 16:21:34 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**copy_arr(char **arr)
{
	char	**new_arr;
	int		len;
	char	**start;

	if (!arr)
		return (0);
	len = ft_arrlen(arr);
	if (!(new_arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (0);
	start = new_arr;
	while (*arr)
		*new_arr++ = *arr++;
	*new_arr = NULL;
	return (start);
}

void		sort_argv(char **arr)
{
	int		cur_index;
	int		len;
	int		arr_end;
	int		current;
	char	*tmp;

	cur_index = 0;
	len = ft_arrlen(arr);
	arr_end = len - 1;
	while (cur_index < len)
	{
		if (*(arr[cur_index]) == '>' || *(arr[cur_index]) == '<')
		{
			tmp = arr[arr_end];
			arr[arr_end] = arr[cur_index];
			current = cur_index;
			while (current++ < arr_end - 1)
				arr[current - 1] = arr[current];
			arr[current - 1] = tmp;
			len--;
		}
		else
			cur_index++;
	}
}
