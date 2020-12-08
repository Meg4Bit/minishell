/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:13:57 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/08 03:08:15 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		exit_checker(char *ar)
{
	while (*ar)
	{
		if (*ar == '-' || *ar == '+')
			ar++;
		if (!ft_isdigit(*ar))
			return (0);
		ar++;
	}
	return (1);
}

static int		ft_exiterr(char **var)
{
	ft_stderr("exit: ", var[1], ": numeric argument required\n");
	return (255);
}

int		ft_exit(char **var)
{
	int		i;

	i = 0;
	if (var[1])
	{
		if (!exit_checker(var[1]))
			i = ft_exiterr(var);
		else
		{
			i = ft_atoi(var[1]);
			i = i % 256;
			if (i <= 0 && ft_strlen(var[1]) > 14)
				i = ft_exiterr(var);
		 }
	}
	exit(i);
}
