/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:33:07 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/13 19:21:06 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slash_handler()
{
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	child_slash_handler()
{
	ft_putstr_fd("Quit\n", 1);
}

void	c_handler(int *ptr)
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
