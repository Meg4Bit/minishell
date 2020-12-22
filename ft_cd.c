/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:31:58 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/22 05:26:33 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_checker(char *path, t_list *env_var)
{
	char	*str;

	str = NULL;
	if (path && path[0] == '-')
	{
		str = var_copy("OLDPWD", env_var);
		if (!str || *str == '\0')
		{
			errno = 0;
			return ((char *)((long)error_msg("cd: OLDPWD not set")));
		}
		ft_putendl_fd(str, 1);
	}
	if (!path || path[0] == '~' || path[0] == '\0' || !str)
		if (!(str = var_copy("HOME", env_var)))
		{
			errno = 0;
			return ((char *)((long)error_msg("cd: HOME not set")));
		}
	return (str);
}

static char	*path_get(char *path, t_list *env_var)
{
	char	*str;

	if (!path || path[0] == '\0' || path[0] == '-' || path[0] == '~')
		str = path_checker(path, env_var);
	else
	{
		if (!(str = ft_strdup(path)))
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
	free_str(&str);
	return (0);
}

static int	pwd_change(char *path, t_list *env_var)
{
	char	*pwd_env;
	char	*pwd_old;
	int		i;

	if (!(pwd_old = var_get("PWD", env_var)))
		pwd_old = var_get("HOME", env_var);
	i = chdir(path);
	if (i == -1)
		return (ft_cderr(path));
	else
	{
		if (!(pwd_env = getcwd((char *)NULL, 0)))
			return (error_msg(""));
		ft_set("OLDPWD=", pwd_old, env_var);
		ft_set("PWD=", pwd_env, env_var);
		free(pwd_env);
	}
	return (1);
}

int			ft_cd(char **var, t_list *env_var)
{
	int		len;
	char	*path;

	len = ft_arrlen(var);
	if (len > 2)
	{
		errno = 0;
		return (error_msg("cd: too many arguments"));
	}
	else
	{
		if (!(path = path_get(var[1], env_var)))
			return (0);
		if (path)
		{
			if (!pwd_change(path, env_var))
				return (free_str(&path));
			free(path);
		}
	}
	return (1);
}
