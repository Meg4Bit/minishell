/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/15 15:48:30 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		utils(t_minishell *minishell, int *res)
{
	char		*line;
	char		*copy;

	*res = get_next_line(0, &minishell->line);
	while (!*res && *minishell->line)
	{
		*res = get_next_line(0, &line);
		if (!(copy = ft_strjoin(minishell->line, line)))
			exit(free_str(minishell->line) + free_str(line));
		free(minishell->line);
		free(line);
		minishell->line = copy;
	}
}

int				main(int argc, char **argv, char **env)
{
	t_list		*env_var;
	t_minishell	minishell;
	int			res;

	minishell.env_var = get_env(env);
	minishell.q_mark = 0;
	minishell.cl = 0;
	minishell.fd[0] = 0;
	minishell.fd[1] = 1;
	minishell.fd_init = 0;
	c_handler(&minishell);
	while (1)
	{
		minishell.line = 0;
		signal(SIGQUIT, slash_handler);
		signal(SIGINT, c_handler);
		ft_putstr_fd("prompt > ", 1);
		utils(&minishell, &res);
		if (res < 0 || (!res && !*minishell.line))
			ft_exit(NULL, &minishell);
		if (*minishell.line)
			command_line(minishell.line, &minishell);
		free(minishell.line);
	}
	return (0);
}
