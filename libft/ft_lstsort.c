/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:37:07 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/13 00:06:39 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **env_sorted, void *data, int (*func)())
{
	t_list	*tmp;
	t_list	*lst;

	if ((*env_sorted) && (*func)((*env_sorted)->content, data) <= 0)
	{
		ft_lstsort(&(*env_sorted)->next, data, func);
	}
	else
	{
		lst = ft_lstnew(data);
		tmp = (*env_sorted);
		(*env_sorted) = lst;
		lst->next = tmp;
	}
}
