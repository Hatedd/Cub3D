/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:09:37 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/17 00:11:38 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	ft_freee(tmp);
	return (i);
}

int	ft_floor_ceilling(t_cub3d *cub, char *str)
{
	int	i;
	int	j;

	if ((ft_strncmp(str, "F", 1) == 0 && cub->floor_rgb)
		|| (ft_strncmp(str, "C", 1) == 0 && cub->ceilling_rgb))
		return (0);
	i = 1;
	while (check_ws(str[i]))
		i++;
	j = i;
	while (ft_isprint(str[j]))
		j++;
	if (ft_strncmp(str, "F", 1) == 0 || ft_strncmp(str, "C", 1) == 0)
	{
		if (!ft_isdigit(str[i]))
			exit(write(2, "Invalide rgb\n", 14));
		if (ft_strncmp(str, "F", 1) == 0)
			cub->floor_rgb = ft_substr(str, i, j);
		else if (ft_strncmp(str, "C", 1) == 0)
			cub->ceilling_rgb = ft_substr(str, i, j);
	}
	if (cub->floor_rgb && cub->ceilling_rgb)
		i = (ft_check_rgb(cub->floor_rgb) && ft_check_rgb(cub->ceilling_rgb));
	return (i);
}

void	ft_walls_check(t_cub3d *cub, int i, int j, int flag)
{
	int	c;

	c = 0;
	while (cub->map[i + c][j] == ' ')
	{
		if (cub->m_flag)
			if (cub->map[i + c][j - 1] != '1')
				exit(write(2, "Map walls error\n", 17));
		if (flag)
			c--;
		else
			c++;
		if (cub->map[i + c][j] == '1')
		{
			if (cub->m_flag)
				if (cub->map[i + c][j - 1] != '1')
					exit(write(2, "Map walls error\n", 17));
			cub->m_flag = 0;
			break ;
		}
		else if (cub->map[i + c][j] != '1' && cub->map[i + c][j] != ' ')
			exit(write(2, "Map walls error\n", 17));
	}
}
