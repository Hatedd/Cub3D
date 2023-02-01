/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:01:32 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 03:54:29 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*tab;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	tab = (char *)ft_calloc(size + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (++i < ft_strlen(s1))
		tab[i] = s1[i];
	while (i < size)
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	return (tab);
}
