/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 04:00:06 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/22 16:00:45 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*head;

	if (!lst)
		return (0);
	head = lst;
	count = 0;
	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}
