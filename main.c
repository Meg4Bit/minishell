/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:19:42 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/11 12:25:25 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler()
{
	//signal(SIGINT, sighandler_t handler);
	signal(SIGQUIT, SIG_IGN);
}

int		main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*env_var;

	env_var = get_env(env);
	while (1)
	{
		signal(SIGQUIT, slash_handler);
		signal(SIGINT, c_handler);
		ft_putstr_fd("prompt > ", 1);
		if (!get_next_line(0, &line))
		{
			ft_putstr_fd("exit\n", 1);
			ft_exit(argv);
		}
		if (*line)
		{
			//ft_putstr_fd(line, 1);
			command_line(line, env_var);
		}
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