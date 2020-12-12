/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/12 20:06:59 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_msg(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	errno = 0;
	return (0);
}

int		free_str(void *tmp)
{
	if (tmp)
		free(tmp);
	return (0);
}

int		name_setup(char **argv, char **name_prog, t_list *env_var)
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
	if (!func_checker(argv, env_var, 0) && !path)
	{
		free(*name_prog);
		if (!(exe_dir = get_exedir((argv)[0], env_var)))
			return (free_arr(argv));
		if (!(*name_prog = ft_strjoin(exe_dir, (argv)[0])))
		{
			free(exe_dir);
			return (free_arr(argv) + error_msg("malloc"));
		}
		free(exe_dir);
	}
	return (1);
}

int		argv_setup(char ***argv, char ***redirect, t_list *cl, t_list *env_var)
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
	if (!change_argv(*argv, env_var) || !change_argv(*redirect, env_var))
	{
		free_arr(*argv);
		return (free_arr(*redirect));
	}
	return (1);
}

int		open_redirect(char **redirect, int *fd)
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
				if ((fd[1] = open(name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)) == -1)
					return (error_msg(name));
			}
			else
			{
				while (*(++name) == ' ')
					;
				if ((fd[1] = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
					return (error_msg(name));
			}
		}
		else
		{
			if (fd[0] != 0)
				close(fd[0]);
			while (*(++name) == ' ')
				;
			if ((fd[0] = open(name, O_RDONLY)) == -1)
				return (error_msg(name));
		}
		redirect++;
	}
	return (1);
}

int		open_fd(t_list *cl, char **redirect, int *fd, int *pip)
{
	if (cl->next && *(char *)(cl->next->content) == '|')
	{
		if (pipe(pip) == -1)
			;
		fd[1] = pip[1];
	}
	if (!open_redirect(redirect, fd))
		return (free_arr(redirect));
	free_arr(redirect);
	dup2(fd[1], 1);
	dup2(fd[0], 0);
	return (1);
}

int		command_exec(t_list **cl, t_list *env_var, int *fd, int *fd_init)
{
	char	*name_prog;
	char	**argv;
	char	**redirect;
	int		pip[2];
	pid_t	pid;

	if (!argv_setup(&argv, &redirect, *cl, env_var))
		return (error_msg("malloc"));
	if (!name_setup(argv, &name_prog, env_var))
		return (free_arr(redirect));
	for (int i = 0; redirect[i] != 0; i++)
	{
		ft_putstr_fd(redirect[i], 1);
		ft_putstr_fd("\n", 1);
	}
	if (!open_fd(*cl, redirect, fd, pip))
		return (0);
	signal(SIGQUIT, child_slash_handler);
	if (argv[0])
	{
		if (func_checker(argv, env_var, 0))
		{
			if (!(func_checker(argv, env_var, 1)))
				return (0);
		}
		else
		{
			if ((pid = fork()) == -1)
				;
			if (pid > 0)
			{
				wait(NULL);
			}
			if (pid == 0)
			{
				if (execve(name_prog, argv, NULL) == -1)
					exit(127 + error_msg(name_prog));
			}
		}
	}
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 1)
			close(fd[1]);
		dup2(fd_init[1], 1);
		//ft_putnbr_fd(pip[0], 1);
		free_str(name_prog);
		free_arr(argv);
		if ((*cl)->next)
		{
			(*cl) = (*cl)->next;
			if (*(char *)((*cl)->content) == '|')
			{
				fd[0] = pip[0];
				if (!(*cl)->next)
				{
					close(fd[0]);
					fd[0] = dup2(fd_init[0], 0);
				}
			}
		}
		if (*(char *)((*cl)->content) != '|')
			fd[0] = dup2(fd_init[0], 0);
		fd[1] = dup2(fd_init[1], 1);
		ft_putnbr_fd(pip[0], 1);
		(*cl) = (*cl)->next;
	return (1);
}

void	command_line(char *line, t_list *env_var)
{
	t_list	*cl;
	t_list	*start;
	int		fd[2];
	int		fd_init[2];

	fd[0] = 0;
	fd[1] = 1;
	fd_init[1] = dup(fd[1]);
	fd_init[0] = dup(fd[0]);
	cl = list_parser(line);
	start = cl;
	while (cl)
	{
		if (!command_exec(&cl, env_var, fd, fd_init))
			break;
	}
	close(fd_init[1]);
	close(fd_init[0]);
	ft_lstclear(&start, (void *)free_str);
}
