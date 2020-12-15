/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 01:36:28 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/15 11:37:16 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	slash_change(char **main_str, char **argv, char **start, int flag)
{
	if (!copy_set(main_str, *argv, *start))
		return (0);
	*start = (*argv)++;
	*start += (flag || **argv == '\\' || **argv == '$' ||\
												**argv == '"') ? 1 : 0;
	*argv += **argv ? 1 : 0;
	return (1);
}

static int	paste_env(char **main_str, char **argv, char **start,\
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
	if (!(key = ft_strjoin(*main_str, tmp)))
		return (0);
	free(*main_str);
	*main_str = key;
	*start = *argv;
	return (1);
}

static int	quote_change(char **main_str, char **argv, char **start)
{
	if (!copy_set(main_str, *argv, *start))
		return (0);
	(*argv)++;
	if (!(*start = ft_strchr(*argv, '\'')))
		*start = ft_strchr(*argv, '\0');
	if (!copy_set(main_str, *start, *argv))
		return (0);
	*argv = **start ? ++(*start) : *start;
	return (1);
}

static int	dub_quote_change(char **main_str, char **argv, char **start,\
													t_minishell *minishell)
{
	if (!copy_set(main_str, *argv, *start))
		return (0);
	*start = ++(*argv);
	while (**argv && **argv != '"')
	{
		if (**argv == '\\')
		{
			if (!slash_change(main_str, argv, start, 0))
				return (0);
		}
		else if (**argv == '$')
		{
			if (!paste_env(main_str, argv, start, minishell))
				return (0);
		}
		else
			(*argv)++;
	}
	if (!copy_set(main_str, *argv, *start))
		return (0);
	*start = **argv ? ++(*argv) : *argv;
	return (1);
}

int			loop_change(char **main_str, char **argv, char **start,\
												t_minishell *minishell)
{
	if (**argv == '\'')
	{
		if (!quote_change(main_str, argv, start))
			return (free_str(*main_str));
	}
	else if (**argv == '"')
	{
		if (!dub_quote_change(main_str, argv, start, minishell))
			return (free_str(*main_str));
	}
	else if (**argv == '$')
	{
		if (!paste_env(main_str, argv, start, minishell))
			return (free_str(*main_str));
	}
	else if (**argv == '\\')
	{
		if (!slash_change(main_str, argv, start, 1))
			return (free_str(*main_str));
	}
	else
		(*argv)++;
	return (1);
}
