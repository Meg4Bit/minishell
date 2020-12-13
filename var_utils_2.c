/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 01:16:53 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/14 00:47:28 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*var_sort(t_list *env_var)
{
	t_list	*env_sorted;

	env_sorted = 0;
	while (env_var)
	{
		ft_lstsort(&env_sorted, env_var->content, &ft_strcmp);
		env_var = env_var->next;
	}
	return (env_sorted);
}

static int	syntax_checker(char *str)
{
	int		j;
	int		i;

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

void		var_handler(char *str, t_list *env_var)
{
	char	*key;
	char	*value;
	char	*ptr;

	if (syntax_checker(str))
		return ;
	value = "";
	if (!(ptr = ft_strchr(str, '=')))
		ft_set(str, value, env_var);
	else
	{
		key = ft_strndup(str, (ptr - str) + 1);
		value = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		ft_set(key, value, env_var);
		free_str(key);
		free_str(value);
	}
}
