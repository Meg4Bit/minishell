/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:57:24 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/30 19:01:17 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

typedef struct	s_fd
{
	int			fd0;
	int			fd1;
}				t_fd;

typedef struct	s_sfunc
{
	char		*key;
	void		(*value)();
}				t_sfunc;

void	command_line(char *line, t_list *env_var);
int		free_str(void *tmp);
void	skip_quotes(char *line, int *i);
t_list	*list_parser(char *line);
int		add_data_list(t_list **commands, char *start, int len);
void	ft_pwd(char **dir);
int		ft_echo(char **line);
void	ft_env(char ** argv, t_list *env_var);
void	ft_export(char **var, t_list *env_var);
t_list	*get_env(char **env);
int		ft_arrlen(char **arr);
t_list	*ft_lstfind(t_list *start, void *data, int (*func)());
void	ft_set(char *key, char *value, t_list *env_var);
int		var_checker(char *s1, char *s2);
void	ft_unset(char **var, t_list *env_var);
void	ft_cd(char **var, t_list *env_var);
void	ft_stderr(char *func, char *arg, char *err);
void	ft_exit(char **var);

#endif