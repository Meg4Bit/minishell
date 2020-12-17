/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/17 22:35:36 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			name_setup(char **argv, char **name_prog, t_minishell *minishell)
{
	char	*exe_dir;
	char	*tmp;
	int		path;

	if (!(*name_prog = ft_strdup(*argv)))
		return (free_arr(argv) + error_msg("malloc"));
	path = 0;
	tmp = argv[0];
	while (*argv[0])
		if (*(argv[0])++ == '/')
			path = 1;
	argv[0] = tmp;
	if (!func_checker(argv, minishell, 0) && !path)
	{
		free(*name_prog);
		if (!(exe_dir = get_exedir((argv)[0], minishell)))
			return (-1);
		if (!(*name_prog = ft_strjoin(exe_dir, (argv)[0])))
		{
			free(exe_dir);
			return (free_arr(argv) + error_msg("malloc"));
		}
		free(exe_dir);
	}
	return (1);
}

int			argv_setup(char ***argv, char ***redirect, t_list *cl,\
											t_minishell *minishell)
{
	char	**tmp;

	if (!(*argv = exe_parser((char *)cl->content)))
		return (error_msg("malloc"));
	sort_argv(*argv);
	tmp = *argv;
	while (*tmp && **tmp != '>' && **tmp != '<')
		tmp++;
	if (!(*redirect = copy_arr(tmp)))
		return ((int)free_arr(*argv));
	*tmp = NULL;
	if (!(tmp = copy_arr(*argv)))
	{
		free_arr(*argv);
		return ((int)free_arr(*redirect));
	}
	free(*argv);
	*argv = tmp;
	if (!change_argv(*argv, minishell) || !change_argv(*redirect, minishell))
	{
		free_arr(*argv);
		return (free_arr(*redirect));
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

int			open_fd(t_list *cl, char **redirect, int *fd, int *pip)
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
		waitpid(-1, &status, WUNTRACED);
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

int			execution(char **argv, t_minishell *minishell)
{
	int		flag;
	char	*name_prog;

	if (!(flag = name_setup(argv, &name_prog, minishell)))
		return (free_arr(argv));
	if (flag == 1)
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

int			command_exec(t_list **cl, t_minishell *minishell, int *fd,\
															int *fd_init)
{
	char	**argv;
	char	**redirect;
	int		pip[2];

	if (!argv_setup(&argv, &redirect, *cl, minishell))
		return (error_msg("malloc error"));
	open_fd(*cl, redirect, fd, pip);
	free_arr(redirect);
	if (argv[0])
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
