/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 01:16:53 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/22 17:50:37 by ametapod         ###   ########.fr       */
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

void		var_mod(t_list *list, char *key, char *value)
{
	char	*p;
	char	*var_env;

	if (!ft_strchr(list->content, '=') && ft_strchr(key, '='))
	{
		p = ft_strjoin(list->content, "=");
		free(list->content);
		list->content = p;
	}
	else if ((p = ft_strchr(list->content, '=')) && ft_strchr(key, '='))
		p[1] = '\0';
	var_env = ft_strjoin(list->content, value);
	free_str((char **)&list->content);
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
	int		i;
	char	*tmp;

	i = 0;
	if (!s2[i])
		return (1);
	if (!ft_strchr(s2, '='))
	{
		if (!ft_strcmp(s2, s1))
			return (0);
	}
	else if (ft_strchr(s2, '='))
	{
		if (!(tmp = ft_substr(s1, 0, ft_strchr(s1, '=') - s1)))
			return (0);
		if (!ft_strcmp(s1, tmp))
			return (free_str(&tmp));
		free(tmp);
	}
	return (1);
}
