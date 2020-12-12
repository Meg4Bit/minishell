/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 03:04:10 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/13 00:06:54 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_lsttoarr(t_list *env_var)
{
	int		rows;
	char	**arr;

	if (!env_var)
		return (NULL);
	rows = ft_lstsize(env_var);
	if (!(arr = malloc(sizeof(char *) * (rows + 1))))
		return (NULL);
	rows = 0;
	while (env_var)
	{
		arr[rows] = (char *)env_var->content;
		env_var = env_var->next;
		rows++;
	}
	arr[rows] = 0;
	return (arr);
}
