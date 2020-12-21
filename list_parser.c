/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:36:43 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/21 21:49:50 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_data_list(t_list **commands, char *start, int len)
{
	t_list	*add;
	char	*tmp;

	if (!(tmp = ft_substr(start, 0, len)))
		return (error_msg("malloc error"));
	if (!(add = ft_lstnew(tmp)))
		return (free_str(&tmp) + error_msg("malloc error"));
	ft_lstadd_back(commands, add);
	return (1);
}

void		skip_quotes(char *line, int *i)
{
	if (line[*i] == '"')
		while (line[++*i] != '"' && line[*i])
		{
			if (line[*i] == '\\')
				*i += line[*i + 1] ? 1 : 0;
		}
	if (line[*i] == '\'')
		while (line[++*i] != '\'' && line[*i])
			;
}

t_list		*list_parser(char *line, t_list *commands)
{
	char	*start;
	int		i;

	start = line;
	i = 0;
	if (!syntax_checker(line, 0))
		return (0);
	while (line[i])
	{
		if (line[i] == '\\')
			i += line[i + 1] ? 2 : 1;
		skip_quotes(line, &i);
		if (line[i] == ';' || line[i] == '|')
		{
			if (!add_data_list(&commands, start, &line[i] - start))
				return (ft_lstclear(&commands, free));
			start = &line[i];
			if (!add_data_list(&commands, start++, 1))
				return (ft_lstclear(&commands, free));
		}
		i += line[i] && line[i] != '\\' ? 1 : 0;
	}
	if (!add_data_list(&commands, start, (int)ft_strlen(start)))
		return (ft_lstclear(&commands, free));
	return (commands);
}
