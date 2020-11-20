/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 18:22:16 by ametapod          #+#    #+#             */
/*   Updated: 2020/05/09 23:23:08 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (new)
	{
		if (*lst)
		{
			ptr = *lst;
			while ((*lst)->next)
				*lst = (*lst)->next;
			(*lst)->next = new;
			*lst = ptr;
		}
		else
			*lst = new;
	}
	return (new);
}
