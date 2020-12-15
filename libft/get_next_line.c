/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:43:45 by ametapod          #+#    #+#             */
/*   Updated: 2020/12/16 00:03:16 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	submit_line(char **line)
{
	char	*tmp;

	if (!(tmp = ft_substr(*line, 0, ft_strlen(*line) - 1)))
		return (-1);
	free(*line);
	*line = tmp;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			rt;
	char		*copy;

	while (!*line || !ft_strchr(*line, '\n'))
	{
		if (!(rt = read(fd, buf, BUFFER_SIZE)) && !*line)
			return (0);
		buf[rt] = 0;
		copy = *line;
		if (!*line)
			if (!(copy = ft_strjoin("", "")))
				return (-1);
		*line = ft_strjoin(copy, buf);
		free(copy);
		if (!*line)
			return (-1);
		rt = 0;
	}
	if (submit_line(line) != 1)
		return (-1);
	return (1);
}
