/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/14 21:10:51 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char **argv, char **env)
{
	char		*line;
	t_list		*env_var;
	t_minishell	minishell;

	minishell.env_var = get_env(env);
	minishell.q_mark = 0;
	minishell.cl = 0;
	minishell.fd = 0;
	minishell.fd_init = 0;
	c_handler(&minishell.q_mark);
	while (1)
	{
		signal(SIGQUIT, slash_handler);
		signal(SIGINT, c_handler);
		ft_putstr_fd("prompt > ", 1);
		if (!get_next_line(0, &minishell.line))
			ft_exit(NULL, &minishell);
		if (*minishell.line)
			command_line(minishell.line, &minishell);
		free(minishell.line);
	}
	return (0);
}
