/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 00:41:27 by tcarlena          #+#    #+#             */
/*   Updated: 2020/12/20 13:00:11 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_diff(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2[i])
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((s2[i] == '=' || !s2[i]) ? 0 : 1);
}

static void	unset_err(char *str)
{
	ft_putstr_fd("minishell: unset: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": not a valid identifier\n", 1);
}

static int	schecker(char *var)
{
	int		tmp;
	int		i;

	i = -1;
	while (var[++i] && var[i] != '=')
	{
		tmp = ft_isalnum(var[i]);
		if (tmp == 0 && var[i] != '_')
			return (1);
	}
	return (0);
}

int			ft_unset(char **var, t_list *env_var)
{
	int		i;
	int		fl;
	t_list	*start;
	t_list	*rm;

	i = 0;
	fl = 0;
	start = env_var;
	while (var[i])
	{
		if ((ft_strchr(var[i], '=') || (ft_isdigit(var[i][0]))\
			|| schecker(var[i])))
		{
			unset_err(var[i]);
			fl = 1;
			break ;
		}
		if ((rm = ft_lstfind(start, var[i], ft_diff)))
			ft_lstrm(&start, rm, free);
		i++;
	}
	return (fl ? 0 : 1);
}
