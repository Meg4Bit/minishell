/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:57:24 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/12 18:40:08 by ametapod         ###   ########.fr       */
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
# include <dirent.h>
# include "libft/libft.h"

typedef struct	s_fd
{
	int			fd0;
	int			fd1;
}				t_fd;

typedef struct	s_sfunc
{
	char		*key;
	int			(*value)();
}				t_sfunc;

void	command_line(char *line, t_list *env_var);
char	**exe_parser(char *str);
int		free_str(void *tmp);
void	skip_quotes(char *line, int *i);
t_list	*list_parser(char *line);
//int		add_data_list(t_list **commands, char *start, int len);
int		ft_pwd(char **dir);
int		ft_echo(char **line);
int		ft_env(char ** argv, t_list *env_var);
int		ft_export(char **var, t_list *env_var);
t_list	*get_env(char **env);
int		ft_arrlen(char **arr);
int		free_arr(char **arr);
void	ft_arriter(char **arr, t_list *env_var, void (*func)(char *, t_list *));
t_list	*ft_lstfind(t_list *start, void *data, int (*func)());
void	ft_set(char *key, char *value, t_list *env_var);
int		var_checker(char *s1, char *s2);
void	var_add(char *key, char *value, t_list *env_var);
void	var_mod(t_list *list, char *value);
char	*var_get(char *key, t_list *env_var);
char	*var_copy(char *key, t_list *env_var);
void	var_handler(char *str, t_list *env_var);
t_list	*var_sort(t_list *env_var);
int		ft_unset(char **var, t_list *env_var);
int		ft_cd(char **var, t_list *env_var);
void	ft_stderr(char *func, char *arg, char *err);
int		ft_exit(char **var);
int		func_checker(char **argv, t_list *env_var, int flag);
void	put_env(void *content);
void	slash_handler();
void	child_slash_handler();
void	c_handler();
void	ft_pass(void *p);
//int		syntax_checker(char *str);
int		change_argv(char **argv, t_list *env_var);
int		loop_change(char **main_str, char **argv, char **start, t_list *env_var);
int		copy_set(char **main_str, char *argv, char *start);
char	*get_exedir(char *exe, t_list *env_var);
char	**exe_parser(char *str);
char	**copy_arr(char **arr);
void	sort_argv(char **arr);

#endif