/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:33:36 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 02:33:18 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*td;
	char	*ts;

	i = 0;
	td = (char *) dst;
	ts = (char *) src;
	if (td < ts)
	{
		while (i < len)
		{
			td[i] = ts[i];
			i++;
		}
	}
	else if (td > ts)
	{
		while (len--)
			td[len] = ts[len];
	}
	return ((void *)td);
}
