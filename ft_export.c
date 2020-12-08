/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:13:57 by tcarlena          #+#    #+#             */
/*   Updated: 2020/11/22 02:12:11 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_stderr(char *func, char *arg, char *err)
{
	ft_putstr_fd(func, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(err, 2);
}

int		syntax_checker(char *str)
{
	int 		j;
	int			i;

	i = -1;
	if (str[0] == '=')
		ft_stderr("export: ", str, ": not a valid identifier\n");
	while (str[++i] && str[i] != '=')
	{
		j = ft_isalnum(str[i]);
		if (j == 0 && str[i] != '_')
		{
			ft_stderr("export: ", str, ": not a valid identifier\n");
			return (1);
		}
	}
	return (0);
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

static void		put_export(void *content)
{
	ft_putstr_fd("declare -x ", 1);
	if (ft_strchr((char *)content, '='))
	{
		ft_putstr_fd("\"", 1);
		ft_putstr_fd((char *)content, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd((char *)content, 1);
		ft_putstr_fd("\n", 1);
	}
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
		ft_lstclear(&env_sorted, &ft_pass);
		return (1);
	}
	else
		ft_arriter(var + 1, env_var, &var_handler);
	return (1);
}