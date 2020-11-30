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

void	ft_arrfree(char **arr)
{
	if (arr && *arr)
	{
		free(*arr);
		*arr = 0;
	}
}

static void		var_add(char *key, char *value, t_list *env_var)
{
	char		*var;
	t_list		*list;

	var = ft_strjoin(key, value);
	list = ft_lstnew(var);
	if (!list)
	{
		free(var);
		exit(1);
	}
	ft_lstadd_back(&env_var, list);
}

static void		var_mod(t_list *list, char *value)
{
	char		*p;
	char		*var_env;

	if ((p = ft_strchr(list->content, '=')))
		p[1] = '\0';
	var_env = ft_strjoin(list->content, value);
	free_str(list->content);
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

static char		*path_checker(char *path, t_list *env_var)
{
	char			*str;

	if (path && path[0] == '-')
		str = var_copy("OLDPWD", env_var);
	if (!path || path[0] == '~' || path[0] == '\0' || !str)
		str = var_copy("HOME", env_var);
	if (!str)
	{
		ft_stderr("cd: ", "HOME", " not set\n");
	}
	return (str);
}

static char		*path_get(char *path, t_list *env_var)
{
	char		*str;

	if (!path || path[0] == '\0' || path[0] == '-' || path[0] == '~')
	{
		str = path_checker(path, env_var);
	}
	else
	{
		str = ft_strdup(path);
		if (!str)
			exit(1);
	}
	return (str);
}

static void		put_env(void *content)
{
	char		*env_var;

	env_var = (char *)content;
	if (ft_strchr(env_var, '='))
	{
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

static void			ft_cderr(char *path)
{
	char			*str;
	char			*err;

	err = strerror(errno);
	str = ft_strjoin(": ", err);
	if (!str)
	{
		exit(1);
	}
	ft_stderr("cd: ", path, str);
	ft_putstr_fd("\n", 2);
	ft_arrfree(&str);
}

static	void	pwd_change(char *path, t_list *env_var)
{
	char		*pwd_env;
	char		*pwd_old;
	int			i;

	pwd_old = var_get("PWD", env_var);
	i = chdir(path);
	if (i == -1)
	{
		ft_cderr(path);
	}
	else
	{
		pwd_env = getcwd((char *)NULL, 0);
		ft_set("OLDPWD", pwd_old, env_var);
		ft_set("PWD", pwd_env, env_var);
		ft_arrfree(&pwd_env);
	}
}

void		ft_cd(char **var, t_list *env_var)
{
	int		len;
	char	*path;

	len = ft_arrlen(var);
	if (len > 2)
	{
		ft_stderr("cd:", " ", "too many argument\n");
		exit(1);
	}

	else
	{
		path = path_get(var[1], env_var);
		if (path)
		{
			pwd_change(path, env_var);
			free(path);
		}
	}
}
