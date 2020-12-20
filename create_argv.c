/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:31:25 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/20 03:08:45 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_redirect(int flag, char *str, int *i)
{
	if (!flag && (str[*i] == '>' || str[*i] == '<'))
	{
		*i += str[*i + 1] == '>' ? 2 : 1;
		while (str[*i] == ' ')
			(*i)++;
		return (1);
	}
	return (flag);
}

static int	argv_len(char *str)
{
	int		i;
	int		flag;
	int		len;

	i = 0;
	flag = (str[i] == '<' || str[i] == '>') ? 0 : 1;
	len = *str ? 1 : 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += str[i + 1] ? 2 : 1;
		flag = skip_redirect(flag, str, &i);
		if (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		{
			len++;
			while (str[i] == ' ')
				i++;
			flag = (str[i] == '<' || str[i] == '>') ? 0 : 1;
		}
		skip_quotes(str, &i);
		i += (str[i] && str[i] != '>' && str[i] != '<'\
									&& str[i] != '\\') ? 1 : 0;
	}
	return (len);
}

static void	koctbljlb(int *flag, char *str, int *i, char **start)
{
	while (str[*i] == ' ')
		(*i)++;
	*start = &str[*i];
	*flag = (str[*i] == '<' || str[*i] == '>') ? 0 : 1;
}

static int	create_arr(char **argv, char *str, int j, int flag)
{
	char	*start;
	int		i;

	i = 0;
	start = str;
	while (str[i])
	{
		if (str[i] == '\\')
			i += str[i + 1] ? 2 : 1;
		flag = skip_redirect(flag, str, &i);
		if (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		{
			if (!(argv[j++] = ft_substr(start, 0, &str[i] - start)))
				return (0);
			koctbljlb(&flag, str, &i, &start);
		}
		skip_quotes(str, &i);
		i += (str[i] && str[i] != '>' && str[i] != '<'\
									&& str[i] != '\\') ? 1 : 0;
	}
	if (!(argv[j++] = ft_substr(start, 0, &str[i] - start)))
		return (0);
	argv[j] = NULL;
	return (1);
}

char		**exe_parser(char *str, t_minishell *minishell)
{
	char	**argv;
	char	*copy;
	int		flag;

	if (!(str = ft_strtrim_mod(str, ' ')))
		return (NULL);
	if (!(copy = str_env(str, minishell)))
		return ((char **)((long)free_str(&str)));
	free(str);
	str = copy;
	if (!(argv = (char **)malloc(sizeof(char *) * (argv_len(str) + 1))))
		return ((char **)((long)free_str(&str)));
	flag = (*str == '<' || *str == '>') ? 0 : 1;
	if (!create_arr(argv, str, 0, flag))
	{
		free(str);
		return ((char **)((long)free_arr(argv)));
	}
	free(str);
	return (argv);
}
