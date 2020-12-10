/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 16:24:31 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/10 16:23:41 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		func_checker(char **argv, t_list *env_var)
{
	t_sfunc	*funct;
	int		i;

	i = 0;
	funct = (t_sfunc[]){
		(t_sfunc){"pwd", ft_pwd},
		(t_sfunc){"echo", ft_echo},
		(t_sfunc){"env", ft_env},
		(t_sfunc){"export", ft_export},
		(t_sfunc){"unset", ft_unset},
		(t_sfunc){"cd", ft_cd},
		(t_sfunc){"exit", ft_exit},
		(t_sfunc){NULL, NULL},
	};
	while (funct[i].key)
	{
		if (!ft_strncmp(funct[i].key, argv[0], ft_strlen(argv[0])))
		{
			if (!(funct[i].value(argv, env_var)))
				return (0);
			return (1);
		}
		i++;
	}
}
