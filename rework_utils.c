/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rework_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 19:40:21 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/22 12:49:41 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		wait_all(char ch)
{
	if (ch != '|')
		while (wait(NULL) > 0)
			;
}

void		wait_last(t_minishell *minishell, t_list *cl, pid_t pid, int flag)
{
	int		status;

	if (flag && (!cl || *(char *)(cl->content) != '|'))
	{
		waitpid(pid, &status, 0);
		if (!(minishell->q_mark = WTERMSIG(status)))
			minishell->q_mark = WEXITSTATUS(status);
		else
			minishell->q_mark += 128;
	}
}

int			close_fd(int *fd, int *fd_init)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	fd[0] = dup2(fd_init[0], 0);
	fd[1] = dup2(fd_init[1], 1);
	return (0);
}

void		free_execve(char **argv, char **name_prog, t_minishell *minishell,\
														char **env)
{
	minishell->q_mark = errno == ENOENT ? 127 : 126;
	error_msg(*name_prog);
	free_arr(argv);
	free_str(name_prog);
	free(env);
	free_minishell(minishell);
	exit(minishell->q_mark);
}
