/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 02:07:56 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 16:02:41 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*tab;
	size_t			len;
	size_t			count;
	unsigned int	start;

	if (!s1 || !set)
		return (NULL);
	if (*set == '\0')
		return (ft_strdup((const char *)s1));
	start = 0;
	while (ft_strchr((char *)set, s1[start]) != 0 && s1[start])
		start++;
	if (s1[start] == 0)
		return (ft_strdup(""));
	len = ft_strlen((s1));
	while (ft_strchr((char *)set, s1[len]) != 0)
		len--;
	count = len - start;
	tab = ft_substr(s1, start, count + 1);
	if (!tab)
		return (NULL);
	return (tab);
}
