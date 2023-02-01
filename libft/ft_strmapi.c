/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 06:00:00 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/22 15:18:37 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*tab;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	tab = ft_calloc((len + 1), sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = f(i, s[i]);
		i++;
	}
	return (tab);
}
