/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:04:57 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/17 00:24:09 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_mid_help(t_cub3d *cub, int i, size_t j)
{
	if ((j >= ft_strlen(cub->map[i - 1]) || \
		j >= ft_strlen(cub->map[i + 1])) && cub->map[i + 1])
		exit(write(2, "Invalide map\n", 14));
	if (j == 0)
		exit(write(2, "Invalide map\n", 14));
	if ((cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == ' ' || \
		cub->map[i][j - 1] == ' ' || cub->map[i][j + 1] == ' ') && \
		cub->map[i][j + 1])
		exit(write(2, "Invalide map\n", 14));
}

void	ft_mid(t_cub3d *cub, int i, size_t j)
{
	size_t	len;
	char	c;

	len = ft_strlen(cub->map[i]);
	while (len > 0 && check_ws(cub->map[i][len - 1]))
	{
		len--;
		if (len == 0)
			break ;
	}
	while (check_ws(cub->map[i][j]) && cub->map[i][j])
		j++;
	while (j < len)
	{
		c = cub->map[i][j];
		if ((c == '0' || c == 'E' || c == 'W' || c == 'S' || c == 'N') && i > 0)
			ft_mid_help(cub, i, j);
		j++;
	}
}

void	ft_ending(t_cub3d *cub, int i, size_t j)
{
	size_t	len;

	len = ft_strlen(cub->map[i]);
	while (check_ws(cub->map[i][len - 1]))
	{
		len--;
		if (len == 0)
			break ;
	}
	while (check_ws(cub->map[i][j]))
		j++;
	while (j < len)
	{
		ft_walls_check(cub, i, j, 1);
		j++;
	}
}

void	ft_beginning(t_cub3d *cub, int i, size_t j)
{
	size_t	len;

	len = ft_strlen(cub->map[i]);
	while (check_ws(cub->map[i][len - 1]))
		len--;
	while (check_ws(cub->map[i][j]))
		j++;
	while (j < len)
	{
		ft_walls_check(cub, i, j, 0);
		j++;
	}
}

void	ft_chflood(t_cub3d *cub)
{
	int		i;
	size_t	j;

	i = 0;
	cub->m_flag = 1;
	while (i < cub->map_len)
	{
		j = 0;
		if (i == 0)
			ft_beginning(cub, i, j);
		else if (i == cub->map_len - 1)
			ft_ending(cub, i, j);
		else
			ft_mid(cub, i, j);
		i++;
	}
}
