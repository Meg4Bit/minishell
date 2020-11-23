/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:13:57 by tcarlena          #+#    #+#             */
/*   Updated: 2020/11/22 02:12:11 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	if ((!s1 && !s2) || n == 0)
		return (0);
	while (n--)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}

void		*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	sym;

	ptr = (unsigned char *)s;
	sym = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr[i] = sym;
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) *\
	(ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void		ft_sfree(void *ptr)
{
	char	*str;

	if (ptr)
	{
		ft_bzero(ptr, ft_strlen(ptr));
		str = (char *)ptr;
		free(str);
		str = 0;
	}
}

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *ptr;

	if (!*lst)
		*lst = new;
	else
	{
		ptr = ft_lstlast(*lst);
		ptr->next = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list *list;

	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}

t_list	*ft_lstfind(t_list *start, void *data, int (*func)())
{
	while (start)
	{
		if (!(*func)(start->content, data))
			return (start);
		start = start->next;
	}
	return (0);
}

void	ft_lstsort(t_list **env_sorted, void *data, int (*func)())
{
	t_list	*tmp;
	t_list	*lst;

	if ((*env_sorted) && (*func)((*env_sorted)->content, data) <= 0)
	{
		ft_lstsort(&(*env_sorted)->next, data, func);
	}
	else
	{
		lst = ft_lstnew(data);
		tmp = (*env_sorted);
		(*env_sorted) = lst;
		lst->next = tmp;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *list;

	list = *lst;
	while (list)
	{
		del(list->content);
		free(list);
		list = list->next;
	}
	*lst = NULL;
}


char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		exit(1);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int		ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int		ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

char		*ft_strndup(const char *s, int n)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen(s);
	if ((n > len))
		n = len;
	if (!(ptr = malloc(sizeof(char) * (n + 1))))
		return (0);
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int		ft_arrlen(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
	{
		len++;
	}
	return (len);
}

void	ft_arriter(char **arr, t_list *env_var, void (*func)(char *, t_list *))
{
	int i;
	t_list *tmp;

	tmp = env_var;

	i = 0;
	while (arr[i])
	{
		(*func)(arr[i], tmp);
		i++;
	}
}

void	ft_pass(void *p)
{
	(void)p;
}

t_list		*get_env(char **env)
{
	int		i;
	t_list	*start;
	t_list	*new;
	char	*str;

	if (!env || !*env)
		exit(1);
	start = 0;
	i = -1;
	while (env[++i])
	{
		if (!(str = ft_strdup(env[i])))
			exit(1);
		if (!(new = ft_lstnew(str)))
			exit(1);
		ft_lstadd_back(&start, new);
	}
	return (start);
}

int			var_checker(char *s1, char *s2)
{
	int		len;

	len = 0;
	if(!s2[len])
		return (1);
	while (s1[len] && s1[len] != '=')
	{
		len++;
	}
	len = ft_memcmp(s1, s2, len);
	if (len == 0)
	{
		return (0);
	}
	return (1);
}

void	ft_stderr(char *func, char *arg, char *err)
{
	ft_putstr_fd(func, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(err, 2);
}

static int		syntax_checker(char *str)
{
	int 		j;
	int			i;

	i = -1;
	if (str[0] == '=')
		ft_stderr("export: ", str, ": not a valid identifier\n");
	while (str[++i] && str[i] != '=')
	{
		j = ft_isalnum(str[i]);
		if (j == 0 && str[i] != '_')
		{
			ft_stderr("export: ", str, ": not a valid identifier\n");
			return (1);
		}
	}
	return (0);
}

static void		var_add(char *key, char *value, t_list *env_var)
{
	char		*var;
	t_list		*list;

	var = ft_strjoin(key, value);
	list = ft_lstnew(var);
	if (!list)
	{
		free(var);
		exit(1);
	}
	ft_lstadd_back(&env_var, list);
}

static void		var_mod(t_list *list, char *value)
{
	char		*p;
	char		*var_env;

	if ((p = ft_strchr(list->content, '=')))
		p[1] = '\0';
	var_env = ft_strjoin(list->content, value);
	ft_sfree(list->content);
	list->content = var_env;
}

void		ft_set(char *key, char *value, t_list *env_var)
{
	t_list	*list;

	list = ft_lstfind(env_var, key, &var_checker);
	if (!list)
	{
		var_add(key, value, env_var);
	}
	else if (value && ft_strlen(value))
	{
		var_mod(list, value);
	}
	(void)list;
}

static void		var_handler(char *str, t_list *env_var)
{
	char		*key;
	char		*value;
	char 		*ptr;

	if (syntax_checker(str))
		return ;
	value = "";
	if (!(ptr = ft_strchr(str, '=')))
		ft_set(str, value, env_var);
	else
	{
		key = ft_strndup(str, (ptr - str) + 1);
		value = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		ft_set(key, value, env_var);
		ft_sfree(key);
		ft_sfree(value);
	}
}

static void		put_env(void *content)
{
	char		*env_var;

	env_var = (char *)content;
	if (ft_strchr(env_var, '='))
	{
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

static void		put_export(void *content)
{
	ft_putstr_fd("declare -x ", 1);
	if (ft_strchr((char *)content, '='))
	{
		ft_putstr_fd("\"", 1);
		ft_putstr_fd((char *)content, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd((char *)content, 1);
}

void	ft_env(t_list	*env_var)
{
	ft_lstiter(env_var, put_env);
}

static t_list 	*var_sort(t_list *env_var)
{
	t_list		*env_sorted;

	env_sorted = 0;
	while (env_var)
	{
		ft_lstsort(&env_sorted, env_var->content, &ft_strcmp);
		env_var = env_var->next;
	}
	return (env_sorted);
}

void	ft_export(char **var, t_list *env_var)
{
	int		len;
	t_list	*env_sorted;

	len = ft_arrlen(var);
	if (len == 1)
	{
		env_sorted = var_sort(env_var);
		ft_lstiter(env_sorted, &put_export);
		ft_lstclear(&env_sorted, &ft_pass);
		return ;
	}
	else
		ft_arriter(var + 1, env_var, &var_handler);
}

int		main(int ac, char **av, char **env)
{
	t_list	*env_var;

	char *tmp[] = {"test=", "ii=", "d", NULL};

	char **data = tmp;

	env_var = get_env(env);
	ft_set("test=", "test", env_var);
	ft_export(data, env_var);
	//ft_env(env_var);
	return (0);
}