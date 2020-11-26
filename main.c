/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/26 12:08:43 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("prompt > ", 1);
		get_next_line(0, &line);
		if (*line)
			command_line(line);
		free(line);
	}
	return (0);
}