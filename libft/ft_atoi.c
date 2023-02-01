/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:53:38 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 03:34:26 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overvalue(unsigned long res, int sign)
{
	if (res)
	{
		if (sign > 0 && res > 9223372036854775807)
			return (-1);
		else if (sign < 0 && res > 9223372036854775808u)
			return (0);
	}
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	unsigned long	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	return (ft_overvalue(r, s));
}
