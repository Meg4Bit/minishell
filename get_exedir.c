/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exedir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:21:42 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/10 03:42:06 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			dir_checker(char *exe, char *env_dir)
{
	DIR				*dirp;
	struct dirent 	*sdir;

	if (!(dirp = opendir(env_dir)))
		return (0);
	while (sdir = readdir(dirp))
	{
		if (!ft_strcmp(sdir->d_name, exe))
		{
			closedir(dirp);
			return (env_dir);
		}
	}
	closedir(dirp);
	return (0);
}

static char			get_exepath(char *exe, char **env_dir)
{
	char			*path;
	int 			i;

	i = 0;
	while (env_dir[i])
	{
		if ((path = dir_checker(exe, env_dir[i])) != 0)
			return (ft_strjoin(path, "/"));
		i++;
	}
	return (0);
}

char			*get_exedir(char **exe, t_list *env_var)
{
	char		*exe_dir;
	char		*var_path;
	char		**env_dir;

	var_path = var_get("PATH", env_var);
	env_dir = ft_split(var_path, ":");
	if (!(exe_dir = get_exepath(exe[0], env_dir)))
		return (0);
	return (exe_dir);
}