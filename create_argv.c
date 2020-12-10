/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:31:25 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/10 21:52:34 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	argv_len(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = *str ? 1 : 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += str[i + 1] ? 2 : 1;
		if (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		{
			len++;
			i += str[i + 1] == '>' ? 2 : 1;
			while (str[i] == ' ')
				i++;
		}
		skip_quotes(str, &i);
		i += (str[i] && str[i] != '>' && str[i] != '<') ? 1 : 0;
	}
	return (len);
}

static int	create_arr(char **argv, char *str, int j)
{
	char	*start;
	int		i;

	i = 0;
	start = str;
	while (str[i])
	{
		if (str[i] == '\\')
			i += str[i + 1] ? 2 : 1;
		if (str[i] == ' ' || str[i] == '>' || str[i] == '<')
		{
			if (!(argv[j++] = ft_substr(start, 0, &str[i] - start)))
				return (0);
			i += str[i + 1] == '>' ? 2 : 1;
			while (str[i] == ' ')
				i++;
			start = (str[i] == '>' || str[i] == '<') ? start : &str[i];
		}
		skip_quotes(str, &i);
		i += (str[i] && str[i] != '>' && str[i] != '<') ? 1 : 0;
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
	if (!create_arr(argv, str, 0))
	{
		free(str);
		return (char **)free_arr(argv);
	}
	free(str);
	return (argv);
}
