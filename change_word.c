/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 00:05:59 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/20 02:39:07 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			copy_set(char **main_str, char *argv, char *start)
{
	char	*copy;
	char	*tmp;

	if (!(tmp = ft_substr(start, 0, argv - start)))
		return (0);
	if (!(copy = ft_strjoin(*main_str, tmp)))
		return (free_str(&tmp));
	free(*main_str);
	free(tmp);
	*main_str = copy;
	return (1);
}

static char	*change_word(char *argv, t_minishell *minishell)
{
	char	*start;
	char	*main_str;

	start = argv;
	if (!(main_str = ft_calloc(1, sizeof(char))))
		return (0);
	while (*argv)
	{
		if (!loop_change(&main_str, &argv, &start, minishell))
			return (0);
	}
	if (!(argv = ft_strjoin(main_str, start)))
		return ((char *)((long)free_str(&main_str)));
	free(main_str);
	return (argv);
}

int			question_env(char **main_str, char **argv, char **start, int q_mark)
{
	char	*str;
	char	*tmp;

	if (**argv == '?')
	{
		if (!(str = ft_itoa(q_mark)))
			return (0);
		if (!(tmp = ft_strjoin(*main_str, str)))
			return (free_str(&str));
		free(*main_str);
		free(str);
		*main_str = tmp;
	}
	*start = ++(*argv);
	return (1);
}

int			change_argv(char **argv, t_minishell *minishell)
{
	char	*copy;

	while (*argv)
	{
		if (!(copy = change_word(*argv, minishell)))
			return (0);
		free(*argv);
		*argv = copy;
		argv++;
	}
	return (1);
}
