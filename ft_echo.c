/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:01:38 by tcarlena          #+#    #+#             */
/*   Updated: 2020/11/19 02:35:23 by tcarlena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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

static int	arg_checker(char **line)
{
	int		i;
	int		j;

	i = 0;
	while (line[++i])
	{
		j = 0;
		if (line[i][j++] == '-')
		{
			while (line[i][j] == 'n')
				j++;
			if (line[i][j] && line[i][j] != 'n')
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int		ft_echo(char **line)
{
	int		i;
	int		flag;

	i = 1;
	flag = 1;
	i = arg_checker(line);
	if (i > 1)
		flag = 0;
	while (line[i])
	{
		ft_putstr_fd(line[i], 1);
		i++;
		if (line[i])
			ft_putstr_fd(" ", 1);
	}
	if (flag == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}

int main(int ac, char **av)
{
	ft_echo(av);
}