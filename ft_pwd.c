/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:49:45 by tcarlena          #+#    #+#             */
/*   Updated: 2020/11/30 17:20:38 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_arrlen(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
	{
		len++;
	}
	return (len);
}

static	int	pwd_err(char *dir)
{
	ft_putstr_fd("pwd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	ft_pwd(char **dir)
{
	char		*wdir;

	if (ft_arrlen(dir) == 1)
	{
		if (!(wdir = getcwd((char *)NULL, 0)))
			pwd_err(dir[0]);
		else
		{
			ft_putstr_fd(wdir, 1);
			free_str(wdir);
		}
	}
	else
	{
		ft_putstr_fd("pwd: ", 2);
		ft_putstr_fd("too many aguments", 2);
	}
	ft_putstr_fd("\n", 1);
}
