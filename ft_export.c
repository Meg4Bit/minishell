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

t_list	*ft_lstfind(t_list *start, void *data, int (*func)())
{
	while (start)
	{
		if (!(*func)(start->content, data))
			return (start);
		start = start->next;
	}
	return (0);
}

void	ft_lstsort(t_list **env_sorted, void *data, int (*func)())
{
	t_list	*tmp;
	t_list	*lst;

	if ((*env_sorted) && (*func)((*env_sorted)->content, data) <= 0)
	{
		ft_lstsort(&(*env_sorted)->next, data, func);
	}
	else
	{
		lst = ft_lstnew(data);
		tmp = (*env_sorted);
		(*env_sorted) = lst;
		lst->next = tmp;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char		*ft_strndup(const char *s, int n)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen(s);
	if ((n > len))
		n = len;
	if (!(ptr = malloc(sizeof(char) * (n + 1))))
		return (0);
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_arriter(char **arr, t_list *env_var, void (*func)(char *, t_list *))
{
	int i;
	t_list *tmp;

	tmp = env_var;

	i = 0;
	while (arr[i])
	{
		(*func)(arr[i], tmp);
		i++;
	}
}

void	ft_pass(void *p)
{
	(void)p;
}

int			var_checker(char *s1, char *s2)
{
	int		len;

	len = 0;
	if(!s2[len])
		return (1);
	while (s1[len] && s1[len] != '=')
	{
		len++;
	}
	len = ft_memcmp(s1, s2, len);
	if (len == 0)
	{
		return (0);
	}
	return (1);
}

void	ft_stderr(char *func, char *arg, char *err)
{
	ft_putstr_fd(func, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(err, 2);
}

static int		syntax_checker(char *str)
{
	int 		j;
	int			i;

	i = -1;
	if (str[0] == '=')
		ft_stderr("export: ", str, ": not a valid identifier\n");
	while (str[++i] && str[i] != '=')
	{
		j = ft_isalnum(str[i]);
		if (j == 0 && str[i] != '_')
		{
			ft_stderr("export: ", str, ": not a valid identifier\n");
			return (1);
		}
	}
	return (0);
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

void		ft_set(char *key, char *value, t_list *env_var)
{
	t_list	*list;

	list = ft_lstfind(env_var, key, &var_checker);
	if (!list)
	{
		var_add(key, value, env_var);
	}
	else if (value && ft_strlen(value))
	{
		var_mod(list, value);
	}
	(void)list;
}

static void		var_handler(char *str, t_list *env_var)
{
	char		*key;
	char		*value;
	char 		*ptr;

	if (syntax_checker(str))
		return ;
	value = "";
	if (!(ptr = ft_strchr(str, '=')))
		ft_set(str, value, env_var);
	else
	{
		key = ft_strndup(str, (ptr - str) + 1);
		value = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		ft_set(key, value, env_var);
		free_str(key);
		free_str(value);
	}
}

static void		put_export(void *content)
{
	ft_putstr_fd("declare -x ", 1);
	if (ft_strchr((char *)content, '='))
	{
		ft_putstr_fd("\"", 1);
		ft_putstr_fd((char *)content, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd((char *)content, 1);
		ft_putstr_fd("\n", 1);
	}
}

static t_list 	*var_sort(t_list *env_var)
{
	t_list		*env_sorted;

	env_sorted = 0;
	while (env_var)
	{
		ft_lstsort(&env_sorted, env_var->content, &ft_strcmp);
		env_var = env_var->next;
	}
	return (env_sorted);
}

void	ft_export(char **var, t_list *env_var)
{
	int		len;
	t_list	*env_sorted;

	len = ft_arrlen(var);
	if (len == 1)
	{
		env_sorted = var_sort(env_var);
		ft_lstiter(env_sorted, &put_export);
		ft_lstclear(&env_sorted, &ft_pass);
		return ;
	}
	else
		ft_arriter(var + 1, env_var, &var_handler);
}