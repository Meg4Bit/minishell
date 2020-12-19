/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:40:22 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/19 03:46:21 by tcarlena         ###   ########.fr       */
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
		var_add(key, value, env_var);
	else
		var_mod(list, key, value);
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
	int		i;
	int		fl;
	t_list	*env_sorted;

	fl = 0;
	i = 0;
	len = ft_arrlen(var);
	if (len == 1)
	{
		env_sorted = var_sort(env_var);
		ft_lstiter(env_sorted, &put_export);
		ft_lstclear(&env_sorted, NULL);
	}
	else
	{
		while (++i < len)
			fl += (ft_arriter(var[i], env_var, &var_handler));
	}
	return (fl != (len - 1) ? 0 : 1);
}
