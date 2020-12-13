/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:53:21 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/14 00:54:02 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			slash_handler(void)
{
	ft_putstr_fd("\b\b  \b\b", 1);
}

void			child_slash_handler(void)
{
	ft_putstr_fd("Quit\n", 1);
}

void			c_handler(int *ptr)
{
	static int	*q_mark = NULL;

	if (q_mark == NULL)
		q_mark = ptr;
	else
	{
		*q_mark = 130;
		ft_putstr_fd("\nprompt > ", 1);
	}
}
