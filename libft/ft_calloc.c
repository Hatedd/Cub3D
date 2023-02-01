/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:57:05 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 03:36:31 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	t_count;
	char	*ptr;

	t_count = count * size;
	ptr = malloc(t_count);
	if (!ptr)
		return (NULL);
	ft_bzero((void *)ptr, t_count);
	return ((void *)ptr);
}
