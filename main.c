/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/17 22:35:30 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char **argv, char **env)
{
	t_minishell	minishell;
	int			res;

	minishell.env_var = get_env(env);
	minishell.q_mark = 0;
	minishell.cl = 0;
	minishell.fd[0] = 0;
	minishell.fd[1] = 1;
	minishell.fd_init = 0;
	c_handler(&minishell);
	while (argc && *argv)
	{
		minishell.line = 0;
		signal(SIGQUIT, slash_handler);
		signal(SIGINT, c_handler);
		ft_putstr_fd("prompt > ", 1);
		if ((res = get_next_line(0, &minishell.line)) < 1)
			ft_exit(NULL, &minishell);
		if (*minishell.line)
			command_line(minishell.line, &minishell);
		free(minishell.line);
	}
	return (0);
}
