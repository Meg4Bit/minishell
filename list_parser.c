/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:36:43 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/09 22:21:23 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_str(void *tmp)
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
		{
			if (line[*i] == '\\')
				*i += line[*i + 1] ? 2 : 1;
		}
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
		if (line[i] == '\\')
			i += line[i + 1] ? 2 : 1;
		skip_quotes(line, &i);
		if (line[i] == ';' || line[i] == '|')
		{
			if (!add_data_list(&commands, start, &line[i] - start))
				return (0);
			start = &line[i];
			if (!add_data_list(&commands, start++, 1))
				return (0);
		}
		i += line[i] ? 1 : 0;
	}
	if (!add_data_list(&commands, start, (int)ft_strlen(start)))
		return (0);
	return (commands);
}
