/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exedir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:21:42 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/13 14:14:10 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*dir_checker(char *exe, char *env_dir)
{
	DIR				*dirp;
	struct dirent 	*sdir;

	if (!(dirp = opendir(env_dir)))
		return (0); // CHANGE
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

static char		*get_exepath(char *exe, char **env_dir)
{
	char			*path;
	int 			i;

	i = -1;
	//path = 0; // COUDL BE DELETED?
	while (env_dir[++i])
	{
		if ((path = dir_checker(exe, env_dir[i])) != 0)
			return (ft_strjoin(path, "/"));
	}
	return (0);
}

char			*get_exedir(char *exe, t_list *env_var)
{
	char		*exe_dir;
	char		*var_path;
	char		**env_dir;

	if (!(var_path = var_get("PATH", env_var)))
		return (0);
	if (!(env_dir = ft_split(var_path, ':')))
		return (error_msg("malloc"));
	exe_dir = get_exepath(exe, env_dir);
	free_arr(env_dir);
	if (!exe_dir)
	{
		// q_mark = 127; !CHANGE
		ft_putstr_fd(exe, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	return (exe_dir);
}
