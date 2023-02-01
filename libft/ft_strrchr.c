/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:58:12 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 03:27:42 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int) ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == ((char) c))
			return ((char *)&s[len]);
		len--;
	}
	return (0);
}
