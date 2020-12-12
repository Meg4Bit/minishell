/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:31:25 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/12 13:40:56 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_redirect(int flag, char *str, int *i)
{
	if (flag && (str[*i] == '>' || str[*i] == '<'))
		return (0);
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
	flag = 0;
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
			flag = 0;
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
	*flag = 0;
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

char		**exe_parser(char *str)
{
	char	**argv;

	if (!(str = ft_strtrim(str, " ")))
		return (NULL);
	if (!(argv = (char **)malloc(sizeof(char *) * (argv_len(str) + 1))))
		return ((char **)free_str(str));
	if (!create_arr(argv, str, 0, 0))
	{
		free(str);
		return (char **)free_arr(argv);
	}
	free(str);
	return (argv);
}
