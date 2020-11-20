/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/21 00:27:15 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_str(char *tmp)
{
	if (tmp)
		free(tmp);
	return (0);
}

t_list	*list_parser(char *line)
{
	t_list	*commands;
	t_list	*add;
	char	*tmp;
	char	*start;
	int		i;

	commands = NULL;
	start = line;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			while (line[++i] != '"' && line[i]);
		if (line[i] == '\'')
			while (line[++i] != '\'' && line[i]);
		if (line[i] == ';' || line[i] == '|')
		{
			if (!(tmp = ft_substr(start, 0, &line[i] - start)))
				return (0);
			if (!(add = ft_lstnew(tmp)))
				return (free_str(tmp));
			ft_lstadd_back(&commands, add);
			start = &line[i];
			if (!(tmp = ft_substr(start++, 0, 1)))
				return (0);
			if (!(add = ft_lstnew(tmp)))
				return (free_str(tmp));
			ft_lstadd_back(&commands, add);
		}
		i++;
	}
	if (!(tmp = ft_strdup(start)))
		return (0);
	if (!(add = ft_lstnew(tmp)))
		return (free_str(tmp));
	ft_lstadd_back(&commands, add);
	return (commands);
}

void	execute_command(char *line)
{
	t_list	*cl;

	cl = list_parser(line);
	ft_lstiter(cl, ft_putstr_fd);
}