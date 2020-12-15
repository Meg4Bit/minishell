/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:53:21 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/15 15:48:43 by ametapod         ###   ########.fr       */
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

void			c_handler(t_minishell *ptr)
{
	static int	*q_mark = NULL;
	static char	**line = NULL;

	if (q_mark == NULL && !line)
	{
		q_mark = &ptr->q_mark;
		line = &ptr->line;
	}
	else
	{
		if (*line)
		{
			free_str(*line);
			if (!(*line = ft_strdup("")))
				ft_exit(NULL, ptr);
		}
		*q_mark = 130;
		ft_putstr_fd("\nprompt > ", 1);
	}
}

void			child_c_handler(void)
{
	ft_putstr_fd("\n", 1);
}
