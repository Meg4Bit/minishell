/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:43:45 by ametapod          #+#    #+#             */
/*   Updated: 2020/11/20 12:11:39 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	submit_line(char **storage, char **line)
{
	size_t	len;
	char	*tmp;

	if (!(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	**line = 0;
	if (*storage)
	{
		free(*line);
		len = ft_strchr(*storage, '\0') - *storage;
		if (ft_strchr(*storage, '\n'))
			len = ft_strchr(*storage, '\n') - *storage;
		if (!(*line = ft_substr(*storage, 0, len)))
			return (-1);
		if (!(tmp = ft_substr(*storage, len + 1,\
					ft_strchr(*storage, '\0') - *storage)))
			return (-1);
		free(*storage);
		*storage = (*tmp == 0) ? NULL : tmp;
		if (*tmp == 0)
			free(tmp);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*storage = NULL;
	char		buf[BUFFER_SIZE + 1];
	int			rt;
	char		*copy;

	while ((storage && ft_strchr(storage, '\n'))\
					|| (rt = read(fd, buf, BUFFER_SIZE)))
	{
		if (!rt)
			return (submit_line(&storage, line));
		buf[rt] = 0;
		copy = storage;
		if (!storage)
			if (!(copy = ft_strjoin("", "")))
				return (-1);
		storage = ft_strjoin(copy, buf);
		free(copy);
		if (!storage)
			return (-1);
		rt = 0;
	}
	if (submit_line(&storage, line) != 1)
		return (-1);
	return (0);
}
