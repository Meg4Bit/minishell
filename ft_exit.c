/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:13:57 by tcarlena          #+#    #+#             */
/*   Updated: 2020/11/30 19:03:34 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		put_env(void *content)
{
	char		*env_var;

	env_var = (char *)content;
	if (ft_strchr(env_var, '='))
	{
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

void		ft_exit(char **var)
{
	int		i;

	if (var[1])
	{
		// if (exit_checker(var[1]) == -1)
		// 	i = ft_exiterr(var);
		// else
		// {
		// 	i = ft_atoi(var[1]);
		// 	i = i % 256;
		// 	if (i <= 0 && ft_strlen(var[1]) > 14)
		// 	{
		// 		i = ft_exiterr(var);
		// 	}
		// }
		;
	}
	exit(0);
}
