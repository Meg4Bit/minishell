/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/08 19:41:26 by ametapod         ###   ########.fr       */
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


int		argv_len(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = *str ? 1 : 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			len++;
			while (str[i] == ' ')
				i++;
		}
		skip_quotes(str, &i);
		i++;
	}
	return (len);
}

static void	*free_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	return (0);
}

int		create_arr(char **argv, char *str)
{
	char	*start;
	int		i;
	int		j;

	i = 0;
	j = 0;
	start = str;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (!(argv[j++] = ft_substr(start, 0, &str[i] - start)))
				return (0);
			while (str[i] == ' ')
				i++;
			start = &str[i];
		}
		skip_quotes(str, &i);
		i++;
	}
	if (!(argv[j++] = ft_substr(start, 0, &str[i] - start)))
		return (0);
	argv[j] = NULL;
	return (1);
}

char	**exe_parser(char *str)
{
	char	**argv;

	if (!(str = ft_strtrim(str, " ")))
		return (NULL);
	if (!(argv = (char **)malloc(sizeof(char *) * (argv_len(str) + 1))))
		return ((char **)free_str(str));
	if (!create_arr(argv, str))
	{
		free(str);
		return (char **)free_arr(argv);
	}
	free(str);
	return (argv);
}

int		copy_set(char **main_str, char *argv, char *start)
{
	char	*copy;
	char	*tmp;

	if (!(tmp = ft_substr(start, 0, argv - start)))
		return (0);
	if (!(copy = ft_strjoin(*main_str, tmp)))
		return(free_str(tmp));
	free(*main_str);
	free(tmp);
	*main_str = copy;
	return (1);
}

int		paste_env(char **main_str, char **argv, char **start, t_list *env_var)
{
	char	*key;
	char	*tmp;

	if (!copy_set(main_str, *argv, *start))
		return (error_msg("malloc"));
	(*argv)++;
	*start = *argv;
	while (**argv && **argv != '\'' && **argv != '"' && **argv != '$')
		(*argv)++;
	if (!(key = ft_substr(*start, 0, *argv - *start)))
		return (error_msg("malloc"));
	if (!(tmp = var_get(key, env_var)))
		tmp = "";
	free(key);
	if (!(key = ft_strjoin(*main_str, tmp)))
		return (error_msg("malloc"));
	free(*main_str);
	*main_str = key;
	*start = *argv;
	return (1);
}

char	*change_word(char *argv, t_list *env_var)
{
	int		i;
	char	*start;
	char	*tmp;
	char	*main_str;

	i = 0;
	start = argv;
	main_str = ft_calloc(1, sizeof(char));
	while (*argv)
	{
		if (*argv == '\\')
			argv += 2;
		if (*argv == '\'')
		{
			if (!copy_set(&main_str, argv, start))
				return (error_msg("malloc"));
			argv++;
			if (!(start = ft_strchr(argv, '\'')))
				start = ft_strchr(argv, '\0');
			if (!copy_set(&main_str, start, argv))
				return (error_msg("malloc"));
			argv = *start ? ++start : start;
		}
		if (*argv == '"')
		{
			if (!copy_set(&main_str, argv, start))
				return (error_msg("malloc"));
			argv++;
			start = argv;
			while (*argv && *argv != '"')
			{
				if (*argv == '$')
				{
					if (!paste_env(&main_str, &argv, &start, env_var))
						return (0);
				}
				else
					argv++;
			}
			if (!copy_set(&main_str, argv, start))
				return (error_msg("malloc"));
			start = argv ? ++argv : argv;
		}
		if (*argv == '$')
		{
			if (!paste_env(&main_str, &argv, &start, env_var))
				return (0);
		}
		if (*argv && *argv != '\'' && *argv != '"' && *argv != '$')
			argv++;
	}
	tmp = ft_strjoin(main_str, start);
	return (tmp);
}

int		change_argv(char **argv, t_list *env_var)
{
	char	*copy;

	while (*argv)
	{
		if (!(copy = change_word(*argv, env_var)))
			return (0);
		free(*argv);
		*argv = copy;
		argv++;
	}
	return (1);
}

int		command_exec(t_list	**cl, t_list *env_var, int *fd, int *fd_init)
{
	char	*name_prog;
	char	**argv;
	int		pip[2];
	pid_t	pid;

	if (!(argv = exe_parser((char *)(*cl)->content)))
		return (error_msg("malloc"));
	if (!change_argv(argv, env_var))
		return (error_msg("malloc"));
	if (!(name_prog = ft_strjoin("/usr/bin/", argv[0])))
	{
		free_arr(argv);
		return (error_msg("malloc"));
	}
		if ((*cl)->next && *(char *)((*cl)->next->content) == '|')
		{
			if (pipe(pip) == -1)
				;
			fd[1] = pip[1];
		}
		dup2(fd[1], 1);
		dup2(fd[0], 0);
		int res;
		signal(SIGQUIT, child_slash_handler);
		if (!(res = func_checker(argv, env_var)))
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
		free_str(name_prog);
		free_arr(argv);
		if (res == -1)
			return (0);
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
