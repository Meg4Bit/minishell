/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:33:50 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/13 00:03:26 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *start, void *data, int (*func)())
{
	while (start)
	{
		if (!(*func)(start->content, data))
			return (start);
		start = start->next;
	}
	return (0);
}
