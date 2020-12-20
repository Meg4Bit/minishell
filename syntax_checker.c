/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:01:11 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/20 14:05:51 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			syntax_checker(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] != '|' && line[i] != ';' && line[i] != '<' && line[i] != '>')
			i++;
		skip_quotes(line, &i);
		if (line[i] == '\\')
			i++;
		i += line[i] ? 1 : 0;
	}
	return (1);
}
