/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 01:42:19 by yobenali          #+#    #+#             */
/*   Updated: 2021/12/09 21:50:22 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_garbeg(char **saved, char **line)
{
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	free(*saved);
	*saved = NULL;
	return (NULL);
}

char	*strline(char *str)
{
	char	*tab;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!str)
		return (free_garbeg(&str, NULL));
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	tab = (char *)ft_calloc((i + 1), sizeof(char));
	if (!tab)
		return (NULL);
	while (j < i)
	{
		tab[j] = str[j];
		j++;
	}
	return (tab);
}

char	*to_save(char **saved, int size)
{
	char	*new;
	int		i;

	i = 0;
	if (!*saved)
		return (free_garbeg(saved, NULL));
	while (saved[0][size] && saved[0][size] != '\n')
		size++;
	new = (char *)ft_calloc((ft_strlen(*saved) - size + 1), sizeof(char));
	if (!new)
		return (free_garbeg(saved, NULL));
	if (saved[0][size])
		size++;
	while (saved[0][size + i])
	{
		new[i] = saved[0][size + i];
		i++;
	}
	free(*saved);
	*saved = NULL;
	return (new);
}

char	*read_join(char	**saved, char **buf, int len, int fd)
{
	while (len > 0)
	{
		len = read(fd, *buf, 1);
		if (len < 0)
			return (free_garbeg(saved, buf));
		buf[0][len] = '\0';
		*saved = ft_mystrjoin(saved, *buf);
	}
	free(*buf);
	*buf = NULL;
	return (*saved);
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char		*buf;
	int			len;

	if (fd < 0)
		return (NULL);
	buf = (char *)ft_calloc((1 + 1), sizeof(char));
	if (!buf)
		return (NULL);
	len = 1;
	saved = read_join(&saved, &buf, len, fd);
	return (saved);
}
