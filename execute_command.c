/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:39:12 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/21 15:36:58 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_str(char *tmp)
{
	if (tmp)
		free(tmp);
	return (0);
}

int		add_data_list(t_list **commands, char *start, int len)
{
	t_list	*add;
	char	*tmp;

	if (!(tmp = ft_substr(start, 0, len)))
		return (0);
	if (!(add = ft_lstnew(tmp)))
		return (free_str(tmp));
	ft_lstadd_back(commands, add);
	return (1);
}

void	skip_quotes(char *line, int *i)
{
	if (line[*i] == '"')
		while (line[++*i] != '"' && line[*i])
			;
	if (line[*i] == '\'')
		while (line[++*i] != '\'' && line[*i])
			;
}

t_list	*list_parser(char *line)
{
	t_list	*commands;
	char	*start;
	int		i;

	commands = NULL;
	start = line;
	i = 0;
	while (line[i])
	{
		skip_quotes(line, &i);
		if (line[i] == ';' || line[i] == '|')
		{
			if (!add_data_list(&commands, start, &line[i] - start))
				return (0);
			start = &line[i];
			if (!add_data_list(&commands, start++, 1))
				return (0);
		}
		i++;
	}
	if (!add_data_list(&commands, start, (int)ft_strlen(start)))
		return (0);
	return (commands);
}

void	execute_command(char *line)
{
	t_list	*cl;

	cl = list_parser(line);
	ft_lstiter(cl, ft_putstr_fd);
}
