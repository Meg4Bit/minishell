/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:01:38 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/22 12:22:36 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_checker(char **line)
{
	int		i;
	int		j;

	i = 0;
	while (line[++i])
	{
		j = 0;
		if (line[i][j++] == '-' && line[i][j] == 'n')
		{
			while (line[i][j] == 'n')
				j++;
			if (line[i][j] && line[i][j] != 'n')
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int			ft_echo(char **line)
{
	int		i;
	int		flag;

	i = 1;
	flag = 1;
	i = arg_checker(line);
	if (i > 1)
		flag = 0;
	while (line[i])
	{
		ft_putstr_fd(line[i], 1);
		i++;
		if (line[i])
			ft_putstr_fd(" ", 1);
	}
	if (flag == 1)
		ft_putstr_fd("\n", 1);
	return (1);
}
