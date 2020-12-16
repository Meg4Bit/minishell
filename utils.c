/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:25:27 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/16 01:45:29 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_arrlen(char **arr)
{
	int		len;

	len = 0;
	while (arr[len])
	{
		len++;
	}
	return (len);
}

int			free_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	return (0);
}

int		ft_arriter(char **arr, t_list *env_var,\
				int (*func)(char *, t_list *))
{
	int		i;
	t_list	*tmp;

	tmp = env_var;
	i = 0;
	while (arr[i])
	{
		if (!((*func)(arr[i], tmp)))
			return (0);
		i++;
	}
}

int			error_msg(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (*msg)
	{
		ft_putstr_fd(msg, 2);
	}
	if (*msg && errno)
		ft_putstr_fd(": ", 2);
	if (errno)
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	errno = 0;
	return (0);
}

int			free_str(void *tmp)
{
	if (tmp)
		free(tmp);
	tmp = NULL;
	return (0);
}
