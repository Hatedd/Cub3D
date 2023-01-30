/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 01:43:17 by yobenali          #+#    #+#             */
/*   Updated: 2023/01/30 17:38:04 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_mystrlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_mystrchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	return (0);
}

char	*ft_mystrdup(const char *s1)
{
	int		len;
	int		i;
	char	*ptr;

	len = ft_mystrlen(s1);
	ptr = (char *)ft_mycalloc(sizeof(char), (len + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < len)
		ptr[i] = s1[i];
	return (ptr);
}

char	*ft_mystrjoin(char **s1, char *s2)
{
	int		i;
	char	*tab;
	int		s2_len;
	int		s1_len;

	i = -1;
	if (!*s1)
		return (ft_mystrdup(s2));
	s1_len = ft_mystrlen(*s1);
	s2_len = ft_mystrlen(s2);
	tab = (char *)ft_mycalloc((s1_len + s2_len + 1), sizeof(char));
	if (!tab)
		return (NULL);
	while (++i < s1_len)
		tab[i] = s1[0][i];
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	while (--s2_len >= 0)
		tab[i + s2_len] = s2[s2_len];
	return (tab);
}

void	*ft_mycalloc(int count, int size)
{
	int		t_count;
	void	*ptr;
	int		i;

	t_count = count * size;
	ptr = malloc(t_count);
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < t_count)
		((char *)ptr)[i] = 0;
	return (ptr);
}
