/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:40:22 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/16 15:57:55 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_stderr(char *func, char *arg, char *err)
{
	ft_putstr_fd(func, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(err, 2);
}

void		ft_set(char *key, char *value, t_list *env_var)
{
	t_list	*list;

	list = ft_lstfind(env_var, key, &var_checker);
	if (!list)
	{
		var_add(key, value, env_var);
	}
	else if (value && ft_strlen(value))
	{
		var_mod(list, value);
	}
	(void)list;
}

static void	put_export(void *content, int a)
{
	char	*str;

	str = (char *)content;
	ft_putstr_fd("declare -x ", a);
	while (*str && *str != '=')
		ft_putchar_fd(*str++, a);
	if (*str == '=')
	{
		ft_putchar_fd(*str++, a);
		ft_putchar_fd('"', a);
		while (*str)
			ft_putchar_fd(*str++, a);
		ft_putchar_fd('"', a);
	}
	ft_putchar_fd('\n', a);
}

int			ft_export(char **var, t_list *env_var)
{
	int		len;
	t_list	*env_sorted;

	len = ft_arrlen(var);
	if (len == 1)
	{
		env_sorted = var_sort(env_var);
		ft_lstiter(env_sorted, &put_export);
		ft_lstclear(&env_sorted, NULL);
		return (1);
	}
	else
		if (!(ft_arriter(var + 1, env_var, &var_handler)))
			return (0);
	return (1);
}
