/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:30:44 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/01 22:47:18 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_myatoi(const char *str)
{
	int				i;
	unsigned long	r;

	i = 0;
	r = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		if (r > 2147483647)
			exit(write(2, "Invalide rgb\n", 14));
		i++;
	}
	if (str[i] == '-' || str[i] != '\0')
		exit(write(2, "Invalide rgb\n", 14));
	return (r);
}

int	check_ws(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

void	ft_rgb_help(char *rgb, int len)
{
	int	ccheck;
	int	i;

	ccheck = 0;
	while (rgb[len])
	{
		i = 0;
		while (ft_isdigit(rgb[len]) && rgb[len])
		{
			len++;
			i++;
		}
		if (rgb[len] == ',' && rgb[len])
		{
			len++;
			i = 0;
			ccheck++;
		}
		if (!ft_isdigit(rgb[len]) && rgb[len] != ',' && rgb[len])
			exit(write(2, "Invalide rgb data\n", 19));
		if ((ccheck != 2) && !rgb[len])
		{
			exit(write(2, "Invalide rgb data\n", 19));
		}
	}
}

int	ft_check_rgb(char *rgb)
{
	int		i;
	int		len;
	char	**tmp;

	len = 1;
	while (check_ws(rgb[len]))
		len++;
	tmp = ft_split(rgb + len - 1, ',');
	ft_rgb_help(rgb, len);
	i = 0;
	while (tmp[i] != NULL)
	{
		len = ft_myatoi(tmp[i]);
		if (len > 255)
			return (0);
		i++;
	}
	if (i < 3)
		exit(write(2, "Invalide rgb data\n", 19));
	ft_free(tmp);
	return (i);
}
