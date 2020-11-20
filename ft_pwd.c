/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:49:45 by tcarlena          #+#    #+#             */
/*   Updated: 2020/11/20 02:41:47 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

static	int	pwd_err(char *dir)
{
	ft_putstr_fd("pwd: ", 1);
	ft_putstr_fd(dir, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

void	ft_pwd(char **dir)
{
	char		*wdir;

	if (ft_arrlen(dir) == 1)
	{
	   	if (!(wdir = getcwd((char *)NULL, 0)))
			pwd_err(dir[0]);
		else
		{
			ft_putstr_fd(wdir, 1);
			ft_sfree(wdir);
		}
	}
	else
	{
	   	ft_putstr_fd("pwd: ", 1);
		ft_putstr_fd("too many aguments", 1);
	}
	ft_putstr_fd("\n", 1);
}

int main(int ac, char **av)
{
	ft_pwd(av);
	return(0);
}