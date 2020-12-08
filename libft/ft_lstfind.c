/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:33:50 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/08 02:35:33 by tcarlena         ###   ########.fr       */
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