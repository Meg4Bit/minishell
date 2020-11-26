/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:57:24 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/26 17:51:31 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct	s_fd
{
	int			fd0;
	int			fd1;
}				t_fd;

void	command_line(char *line);
int		free_str(void *tmp);
void	skip_quotes(char *line, int *i);
t_list	*list_parser(char *line);
int		add_data_list(t_list **commands, char *start, int len);

#endif