/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 22:05:13 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/21 18:19:54 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			name_setup(char **argv, char **name_prog, t_minishell *minishell)
{
	char	*exe_dir;
	char	*tmp;
	int		path;

	if (!(*name_prog = ft_strdup(*argv)))
		return (error_msg("malloc"));
	path = 0;
	tmp = argv[0];
	while (*argv[0])
		if (*(argv[0])++ == '/')
			path = 1;
	argv[0] = tmp;
	if (!func_checker(argv, minishell, 0) && !path)
	{
		if (!(exe_dir = get_exedir(*name_prog, minishell)))
			return (free_str(name_prog) - 1);
		if (exe_dir != *name_prog)
		{
			free_str(name_prog);
			if (!(*name_prog = ft_strjoin(exe_dir, (argv)[0])))
				return (free_str(&exe_dir) + error_msg("malloc"));
			free(exe_dir);
		}
	}
	return (1);
}

static int	open_fd_one(char *name, int *fd)
{
	if (fd[1] != 1)
		close(fd[1]);
	if (*name == '>')
	{
		while (*(++name) == ' ')
			;
		if ((fd[1] = open(name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
			return (error_msg(name));
	}
	else
	{
		while (*name == ' ')
			name++;
		if ((fd[1] = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (error_msg(name));
	}
	return (1);
}

int			open_redirect(char **redirect, int *fd)
{
	char	*name;

	while (*redirect)
	{
		name = *redirect;
		if (*name++ == '>')
		{
			if (!open_fd_one(name, fd))
				return (0);
		}
		else
		{
			if (fd[0] != 0)
				close(fd[0]);
			while (*name == ' ')
				name++;
			if ((fd[0] = open(name, O_RDONLY)) == -1)
				return (error_msg(name));
		}
		redirect++;
	}
	return (1);
}

int			ft_execve(char **argv, char **name_prog, t_minishell *minishell)
{
	int		status;
	char	**env_var;
	pid_t	pid;

	signal(SIGQUIT, child_slash_handler);
	signal(SIGINT, child_c_handler);
	if (!(env_var = ft_lsttoarr(minishell->env_var)))
		return (error_msg("malloc error"));
	if ((pid = fork()) == -1)
		return (error_msg(""));
	if (pid > 0)
		wait(&status);
	if (pid == 0)
	{
		if (execve(*name_prog, argv, env_var) == -1)
			exit(127 + error_msg(*name_prog));
	}
	free(env_var);
	if (!(minishell->q_mark = WTERMSIG(status)))
		minishell->q_mark = WEXITSTATUS(status);
	else
		minishell->q_mark += 128;
	free_str(name_prog);
	return (1);
}

int			ft_exec(char **argv, t_minishell *minishell, int *flag, t_list *cl)
{
	pid_t	pid;
	int		status;

	pid = 0;
	signal(SIGQUIT, child_slash_handler);
	signal(SIGINT, child_c_handler);
	if (flag[1])
		if ((pid = fork()) == -1)
			return (error_msg(""));
	if (pid == 0)
	{
		if (argv[0] && flag[0])
			execution(argv, minishell);
		else
			minishell->q_mark = flag[0] ? 0 : 1;
		if (flag[1])
		{
			free_arr(argv);
			free_minishell(minishell);
			exit(minishell->q_mark);
		}
	}
	if (flag[1] && (!cl || *(char *)(cl->content) != '|'))
	{
		waitpid(pid, &status, 0);
		if (!(minishell->q_mark = WTERMSIG(status)))
			minishell->q_mark = WEXITSTATUS(status);
		else
			minishell->q_mark += 128;
	}
	return (1);
}
