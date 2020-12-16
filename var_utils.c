/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 01:16:53 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/16 13:14:48 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		var_add(char *key, char *value, t_list *env_var)
{
	char	*var;
	t_list	*list;

	var = ft_strjoin(key, value);
	list = ft_lstnew(var);
	if (!list)
	{
		free(var);
		exit(1);
	}
	ft_lstadd_back(&env_var, list);
}

void		var_mod(t_list *list, char *value)
{
	char	*p;
	char	*var_env;

	if ((p = ft_strchr(list->content, '=')))
		p[1] = '\0';
	var_env = ft_strjoin(list->content, value);
	free_str(&list->content);
	list->content = var_env;
}

char		*var_get(char *key, t_list *env_var)
{
	char	*str;
	int		len;

	while (env_var)
	{
		len = ft_strlen(key);
		str = (char *)env_var->content;
		if (!ft_memcmp(key, str, len))
		{
			if (str[len] == '=')
				return (str + (len + 1));
		}
		env_var = env_var->next;
	}
	return (0);
}

char		*var_copy(char *key, t_list *env_var)
{
	char	*value;
	char	*copy;

	if (env_var)
	{
		value = var_get(key, env_var);
		if (!value)
			return (0);
		else
		{
			copy = ft_strdup(value);
			if (!copy)
				exit(1);
		}
		return (copy);
	}
	return (0);
}

int			var_checker(char *s1, char *s2)
{
	int		len;

	len = 0;
	if (!s2[len])
		return (1);
	while (s1[len] && s1[len] != '=')
	{
		len++;
	}
	len = ft_memcmp(s1, s2, len);
	if (len == 0)
	{
		return (0);
	}
	return (1);
}
