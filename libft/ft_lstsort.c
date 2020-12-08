/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:37:07 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/08 02:37:22 by tcarlena         ###   ########.fr       */
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