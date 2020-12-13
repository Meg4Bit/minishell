/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/14 01:00:27 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			signal_handler(void)
{
	//signal(SIGINT, sighandler_t handler);
	signal(SIGQUIT, SIG_IGN);
}

int				main(int argc, char **argv, char **env)
{
	char		*line;
	t_list		*env_var;
	t_minishell	minishell;

	minishell.env_var = get_env(env);
	minishell.q_mark = 77;
	c_handler(&minishell.q_mark);
	while (1)
	{
		signal(SIGQUIT, slash_handler);
		signal(SIGINT, c_handler);
		ft_putstr_fd("prompt > ", 1);
		if (!get_next_line(0, &line))
			;//ft_exit(argv);
		if (*line)
		{
			//ft_putstr_fd(line, 1);
			command_line(line, &minishell);
		}
		free(line);
	}
	return (0);
}
