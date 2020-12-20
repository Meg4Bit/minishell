/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 02:38:04 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/20 03:13:10 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_quotes(char **arr, char **copy, char **str, int *i)
{
	if (!(*copy = ft_strjoin(*str, "'")))
		return (free_arr(arr) + free_str(str));
	free(*str);
	if (!(*str = ft_strjoin(*copy, arr[(*i)++])))
		return (free_arr(arr) + free_str(copy));
	free(*copy);
	if (!(*copy = ft_strjoin(*str, "'")))
		return (free_arr(arr) + free_str(str));
	free(*str);
	if (arr[(*i)])
	{
		if (!(*str = ft_strjoin(*copy, " ")))
			return (free_arr(arr) + free_str(copy));
		free(*copy);
	}
	return (1);
}

static int	add_key_to_str(char **main_str, char *tmp)
{
	char	**arr;
	char	*copy;
	char	*str;
	int		i;

	i = 0;
	if (!(arr = ft_split(tmp, ' ')) ||\
				!(str = ft_strdup("")))
		return (0);
	while (arr[i])
	{
		if (!add_quotes(arr, &copy, &str, &i))
			return (0);
	}
	free_arr(arr);
	if (!(str = ft_strjoin(*main_str, copy)))
		return (free_str(&copy));
	free(copy);
	free(*main_str);
	*main_str = str;
	return (1);
}

static int	paste_env_two(char **main_str, char **argv, char **start,\
												t_minishell *minishell)
{
	char	*key;
	char	*tmp;

	if (!copy_set(main_str, *argv, *start))
		return (0);
	*start = (*argv)++;
	if (!(**argv) || **argv == '\\')
		return (1);
	if (**argv == '?' || ft_isdigit(**argv))
		return (question_env(main_str, argv, start, minishell->q_mark));
	*start = *argv;
	while (ft_isalnum(**argv) || **argv == '_')
		(*argv)++;
	if (!(key = ft_substr(*start, 0, *argv - *start)))
		return (0);
	if (!(tmp = var_get(key, minishell->env_var)))
		tmp = "";
	free(key);
	if (*tmp)
		if (!add_key_to_str(main_str, tmp))
			return (0);
	*start = *argv;
	return (1);
}

char		*str_env(char *str, t_minishell *minishell)
{
	int		i;
	char	*start;
	char	*main_str;

	start = str;
	if (!(main_str = ft_calloc(1, sizeof(char))))
		return (0);
	while (*str)
	{
		i = 0;
		if (str[i] == '\\')
			i += str[i + 1] ? 2 : 1;
		skip_quotes(str, &i);
		str += i;
		if (*(str) == '$')
		{
			if (!paste_env_two(&main_str, &str, &start, minishell))
				return ((char *)((long)free_str(&main_str)));
		}
		else
			str += str ? 1 : 0;
	}
	if (!(str = ft_strjoin(main_str, start)))
		return ((char *)((long)free_str(&main_str)));
	free(main_str);
	return (str);
}
