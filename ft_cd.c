/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:31:58 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/14 00:32:02 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_checker(char *path, t_list *env_var)
{
	char	*str;

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

static char	*path_get(char *path, t_list *env_var)
{
	char	*str;

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

static int	ft_cderr(char *path)
{
	char	*str;

	if (!(str = ft_strjoin("cd: ", path)))
		return (error_msg("malloc error"));
	error_msg(str);
	free_str(str);
	return (0);
}

static int	pwd_change(char *path, t_list *env_var)
{
	char	*pwd_env;
	char	*pwd_old;
	int		i;

	pwd_old = var_get("PWD", env_var);
	i = chdir(path);
	if (i == -1)
	{
		return (ft_cderr(path));
	}
	else
	{
		if (!(pwd_env = getcwd((char *)NULL, 0)))
			return (error_msg(""));
		ft_set("OLDPWD", pwd_old, env_var);
		ft_set("PWD", pwd_env, env_var);
		free_str(pwd_env);
	}
	return (1);
}

int			ft_cd(char **var, t_list *env_var)
{
	int		len;
	char	*path;

	len = ft_arrlen(var);
	if (len > 2)
		return (error_msg("cd: too many arguments"));
	else
	{
		path = path_get(var[1], env_var);
		if (path)
		{
			if (!pwd_change(path, env_var))
				return (free_str(path));
			free(path);
		}
	}
	return (1);
}
