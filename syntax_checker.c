/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:01:11 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/21 21:54:48 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(char ch)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (ch)
		ft_putchar_fd(ch, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	err_checker(char *line, int *i, char *last, int *flag)
{
	int		b;

	*last = line[*i];
	if (flag[1])
		return (syntax_error(line[*i]));
	if (line[*i] == '|' || line[*i] == ';')
	{
		if (!flag[0])
			return (syntax_error(line[*i]));
		flag[0] = 0;
	}
	else
	{
		flag[1] = 1;
		*i += (line[*i] == '>' && line[*i + 1] == '>') ? 1 : 0;
		b = *i + 1;
		if (!line[b] || line[b] == '|' || line[b] == ';'\
				|| line[b] == '<' || line[b] == '>')
			return (syntax_error(line[b]));
	}
	return (1);
}

static void	set_flag(int *flag)
{
	flag[0] = 1;
	flag[1] = 0;
}

int			syntax_checker(char *line, int i)
{
	int		flag[2];
	char	last;

	flag[0] = 0;
	flag[1] = 0;
	last = line[i];
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != '|' && line[i] != ';' && line[i] != '<' &&\
														line[i] != '>')
			set_flag(flag);
		else
		{
			if (!err_checker(line, &i, &last, flag))
				return (0);
		}
		skip_quotes(line, &i);
		if (line[i] == '\\')
			i++;
		i += line[i] ? 1 : 0;
	}
	return ((last == '|' && !flag[0]) ? syntax_error(line[i]) : 1);
}
