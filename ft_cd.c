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

static char		*path_checker(char *path, t_list *env_var)
{
	char		*str;

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
	free_str(str);
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
		free_str(pwd_env);
	}
}

int		ft_cd(char **var, t_list *env_var)
{
	int		len;
	char	*path;

	len = ft_arrlen(var);
	if (len > 2)
	{
		ft_stderr("cd:", " ", "too many argument\n");
		return (0);
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
	return (1);
}
