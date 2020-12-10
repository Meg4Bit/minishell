/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/11 01:25:47 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (errno)
		perror(msg);
	else
		ft_putstr_fd(msg, 2);
	return (0);
}

int		free_str(void *tmp)
{
	if (tmp)
		free(tmp);
	return (0);
}

int		inbuilt_check(char *name_prog)
{
	int i = 0;
	char	*func[] = {
		"pwd",
		"echo",
		"env",
		"export",
		"unset",
		"cd",
		"exit",
		NULL,
	};
	while (func[i])
	{
		if (!ft_strncmp(func[i], name_prog, ft_strlen(name_prog)))
			return (1);
		i++;
	}
	return (0);
}

char	**copy_arr(char **arr)
{
	char	**new_arr;
	int		len;
	char	start;

	if (!arr)
		return (0);
	len = ft_arrlen(arr);
	if (!(new_arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (0);
	start = new_arr;
	while (*arr)
		*new_arr++ = *arr++;
	*new_arr = NULL;
	return (start);
}

int		name_setup(char **argv, char **name_prog, t_list *env_var)
{
	char	*exe_dir;

	*name_prog = *argv;
	if (!inbuilt_check((argv)[0]))
	{
		if (!(exe_dir = get_exedir((argv)[0], env_var)))
			return (free_arr(argv));
		if (!(*name_prog = ft_strjoin(exe_dir, (argv)[0])))
		{
			free_arr(argv);
			free(exe_dir);
			return (error_msg("malloc"));
		}
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
	tmp = NULL;
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
		return (0);
	for (int i = 0; argv[i] != 0; i++)
	{
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd("\n", 1);
	}
		if ((*cl)->next && *(char *)((*cl)->next->content) == '|')
		{
			if (pipe(pip) == -1)
				;
			fd[1] = pip[1];
		}
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		signal(SIGQUIT, child_slash_handler);
		if (inbuilt_check(argv[0]))
		{
			if (!(func_checker(argv, env_var)))
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
					;
			}
		}
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 1)
			close(fd[1]);
		dup2(fd_init[1], 1);
		//ft_putnbr_fd(pip[0], 1);
		//free_str(name_prog);
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
