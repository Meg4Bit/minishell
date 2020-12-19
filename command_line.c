/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/19 14:32:38 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	argv_setup(char ***argv, char ***redirect, t_list *cl,\
											t_minishell *minishell)
{
	char	**tmp;

	if (!(*argv = exe_parser((char *)cl->content)))
		return (0);
	sort_argv(*argv);
	tmp = *argv;
	while (*tmp && **tmp != '>' && **tmp != '<')
		tmp++;
	if (!(*redirect = copy_arr(tmp)))
		return (free_arr(*argv));
	*tmp = NULL;
	if (!(tmp = copy_arr(*argv)))
		return (free_arr(*argv) + free_arr(*redirect));
	free(*argv);
	*argv = tmp;
	if (!change_argv(*argv, minishell) || !change_argv(*redirect, minishell))
		return (free_arr(*argv) + free_arr(*redirect));
	if (!(tmp = copy_arr(*argv)))
		return (free_arr(*argv) + free_arr(*redirect));
	free(*argv);
	*argv = tmp;
	return (1);
}

static int	open_fd(t_list *cl, char **redirect, int *fd, int *pip)
{
	if (cl->next && *(char *)(cl->next->content) == '|')
	{
		if (pipe(pip) == -1)
			return (error_msg(""));
		fd[1] = pip[1];
	}
	if (!open_redirect(redirect, fd))
		return (0);
	if (dup2(fd[0], 0) == -1)
		return (error_msg(""));
	if (dup2(fd[1], 1) == -1)
		return (error_msg(""));
	return (1);
}

static int	execution(char **argv, t_minishell *minishell)
{
	int		flag;
	char	*name_prog;

	if (!(flag = name_setup(argv, &name_prog, minishell)))
		ft_exit(argv, minishell);
	else if (flag == 1)
	{
		if (func_checker(argv, minishell, 0))
		{
			free_str(&name_prog);
			if (!(func_checker(argv, minishell, 1)))
				return ((minishell->q_mark = 1));
			minishell->q_mark = 0;
		}
		else
		{
			if (!ft_execve(argv, &name_prog, minishell))
			{
				free_str(&name_prog);
				ft_exit(argv, minishell);
			}
		}
	}
	return (1);
}

static int	command_exec(t_list **cl, t_minishell *minishell, int *fd,\
															int *fd_init)
{
	char	**argv;
	char	**redirect;
	int		pip[2];
	int		flag;

	redirect = NULL;
	if (!argv_setup(&argv, &redirect, *cl, minishell))
		return (error_msg("malloc error"));
	flag = open_fd(*cl, redirect, fd, pip);
	free_arr(redirect);
	if (argv[0] && flag)
		execution(argv, minishell);
	close_fd(fd, fd_init);
	free_arr(argv);
	if ((*cl)->next)
	{
		(*cl) = (*cl)->next;
		if (*(char *)((*cl)->content) == '|')
			fd[0] = pip[0];
	}
	(*cl) = (*cl)->next;
	return (1);
}

void		command_line(char *line, t_minishell *minishell)
{
	t_list	*cl;
	int		fd_init[2];

	fd_init[1] = dup(minishell->fd[1]);
	fd_init[0] = dup(minishell->fd[0]);
	minishell->fd_init = fd_init;
	cl = list_parser(line, NULL);
	minishell->cl = cl;
	while (cl && *(char *)(cl->content))
	{
		if (!command_exec(&cl, minishell, minishell->fd, minishell->fd_init))
			ft_exit(NULL, minishell);
	}
	close_fd(minishell->fd, fd_init);
	close(minishell->fd_init[1]);
	close(minishell->fd_init[0]);
	ft_lstclear(&(minishell->cl), free);
	minishell->fd_init = 0;
	minishell->cl = 0;
}
