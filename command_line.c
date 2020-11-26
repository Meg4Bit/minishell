/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/26 18:28:29 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (arr)
	{
		while (*arr)
			free(*arr++);
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
		return ;
	if (!(argv = (char **)malloc(sizeof(char *) * (argv_len(str) + 1))))
		return free_str(str);
	if (!create_arr(argv, str))
	{
		free(str);
		return free_arr(argv);
	}
	free(str);
	return (argv);
}

void	command_line(char *line)
{
	t_list	*cl;
	t_list	*start;
	int		fd[2];
	int		pip[2];
	int		fd0;
	int		fd1;
	pid_t	pid;

	fd[0] = 0;
	fd[1] = 1;
	fd1 = dup(fd[1]);
	fd0 = dup(fd[0]);
	cl = list_parser(line);
	start = cl;
	char	*argv[] = {"ls", NULL};
	while (cl)
	{
		char	*name_prog;
		char	**argv;
		dup2(fd1, 1);
		if (!(argv = exe_parser((char *)cl->content)))
			;
		if (!(name_prog = ft_strjoin("/usr/bin/", argv[0])))
			;
		if (cl->next && *(char *)(cl->next->content) == '|')
		{
			if (pipe(pip) == -1)
				;
			if ((fd[0] = dup2(pip[0], fd[0])) == -1)
				;
			if ((fd[1] = dup2(pip[1], fd[1])) == -1)
				;
			cl = cl->next;
			//if (!cl->next)
		}
		if ((pid = fork()) == -1)
			;
		if (pid == 0)
			if (execve(name_prog, argv, NULL) == -1)
				;
		wait(NULL);
		cl = cl->next;
	}
	dup2(fd0, 0);
	//ft_lstiter(cl, ft_putstr_fd);
	ft_lstclear(&start, (void *)free_str);
}
