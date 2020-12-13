/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:13:57 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/13 14:15:39 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_list		*get_env(char **env)
{
	int		i;
	t_list	*start;
	t_list	*new;
	char	*str;

	if (!env || !*env)
		exit(1);
	start = 0;
	i = -1;
	while (env[++i])
	{
		if (!(str = ft_strdup(env[i])))
			exit(1);
		if (!(new = ft_lstnew(str)))
			exit(1);
		ft_lstadd_back(&start, new);
	}
	return (start);
}

static void	put_env(void *content)
{
	char		*env_var;

	env_var = (char *)content;
	if (ft_strchr(env_var, '='))
	{
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

int	ft_env(char ** argv, t_list *env_var)
{
	argv = NULL;
	ft_lstiter(env_var, put_env);
	return (1);
}
