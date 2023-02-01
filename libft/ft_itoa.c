/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 03:50:34 by yobenali          #+#    #+#             */
/*   Updated: 2021/11/21 20:13:10 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_calcul(long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static char	*ft_toconvert(char *tab, long nb, int len)
{
	if (nb < 0)
	{
		tab[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
	{
		tab[0] = 48;
		return (tab);
	}
	while (nb)
	{
		tab[len - 1] = nb % 10 + '0';
		nb /= 10;
		len--;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;
	long	nb;
	int		len;

	nb = (long) n;
	len = ft_calcul(nb);
	tab = (char *)ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (NULL);
	return (ft_toconvert(tab, nb, len));
}
