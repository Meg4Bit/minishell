/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/30 18:18:08 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*env_var;

	env_var = get_env(env);
	while (1)
	{
		ft_putstr_fd("prompt > ", 1);
		get_next_line(0, &line);
		if (*line)
			command_line(line, env_var);
		free(line);
	}
	/*int a;
	a = open("a.txt", O_RDWR);
	close(a);
	ft_putnbr_fd(a, 1);
	a = open("a.txt", O_RDWR);
	close(a);
	ft_putnbr_fd(a, 1);
	a = open("a.txt", O_RDWR);
	close(a);
	ft_putnbr_fd(a, 1);*/
	return (0);
}