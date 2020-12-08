/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 02:25:27 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/08 02:52:41 by tcarlena         ###   ########.fr       */
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

void	ft_arrfree(char **arr)
{
	if (arr && *arr)
	{
		free(*arr);
		*arr = 0;
	}
}

void	ft_arriter(char **arr, t_list *env_var, void (*func)(char *, t_list *))
{
	int i;
	t_list *tmp;

	tmp = env_var;

	i = 0;
	while (arr[i])
	{
		(*func)(arr[i], tmp);
		i++;
	}
}

void	ft_pass(void *p)
{
	(void)p;
}