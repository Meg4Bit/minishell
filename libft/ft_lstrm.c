/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:57:19 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/08 02:58:33 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstrm(t_list **env_var, t_list *rm, void (*func)(void *))
{
	t_list	*tmp;

	if (env_var && *env_var)
	{
		if (*env_var == rm)
		{
			tmp = (*env_var);
			(*env_var) = tmp->next;
			(*func)(tmp->content);
			free(tmp);
			tmp = 0;
		}
		else
			ft_lstrm(&(*env_var)->next, rm, func);
	}
}
