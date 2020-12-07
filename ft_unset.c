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

int		ft_diff(char *s1, char *s2)
{
	int	i;

	i = 0;
	if(!s2[i])
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((s2[i] == '=' || !s2[i]) ? 0 : 1);
}

 void		ft_lstrm(t_list **env_var, t_list *rm, void (*func)(void *))
 {
 	t_list	*tmp;

 	if (env_var && *env_var)
 	{
 		if (*env_var == rm)
 		{
 			tmp = (*env_var);
 			(*env_var) = tmp->next;
 			(*func)(tmp->content);
 			free(tmp);
 			tmp = 0;
 		}
 		else
 			ft_lstrm(&(*env_var)->next, rm, func);
 	}
 }

static void	unset_err(char *str)
{
	ft_putstr_fd("unset: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": invalid parameter name\n", 1);
}

void		ft_unset(char **var, t_list *env_var)
{
	int		i;
	t_list	*start;
	t_list	*rm;

	i = 0;
	start = env_var;
	while (var[i])
	{
		if (ft_strchr(var[i], '='))
		{
			unset_err(var[i]);
			break;
		}
		if ((rm = ft_lstfind(start, var[i], ft_diff)))
		{
			ft_lstrm(&start, rm, free_str);
			//continue;
		}
		i++;
	}
}
