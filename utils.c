/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:25:27 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/14 12:38:01 by ametapod         ###   ########.fr       */
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

void		ft_arriter(char **arr, t_list *env_var,\
				void (*func)(char *, t_list *))
{
	int		i;
	t_list	*tmp;

	tmp = env_var;
	i = 0;
	while (arr[i])
	{
		(*func)(arr[i], tmp);
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
	return (0);
}
