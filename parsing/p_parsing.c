/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:30:39 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 17:30:43 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_pos_xy(t_cub3d *cub)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < cub->map_len)
	{
		j = 0;
		len = ft_strlen(cub->map[i]);
		while (j < len)
		{
			if (cub->map[i][j] == 'S' || cub->map[i][j] == 'N' || \
				cub->map[i][j] == 'E' || cub->map[i][j] == 'W')
			{
				cub->pos_x = j;
				cub->pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	player_dire(t_cub3d *cub, int line)
{
	int	i;

	i = 0;
	ft_pos_xy(cub);
	while (cub->map[line][i])
	{
		if (cub->map[line][i] == 'S' || cub->map[line][i] == 'N' || \
			cub->map[line][i] == 'E' || cub->map[line][i] == 'W')
		{
			cub->p_direction = cub->map[line][i];
			cub->map[line][i] = '0';
			break ;
		}
		i++;
	}
	return (1);
}

int	player_pos(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < cub->map_len)
	{
		if (ft_strchr(cub->map[i], 'E') || ft_strchr(cub->map[i], 'S') || \
			ft_strchr(cub->map[i], 'N') || ft_strchr(cub->map[i], 'W'))
		{
			player_dire(cub, i);
			cub->p_flag++;
		}
		i++;
	}
	ft_chflood(cub);
	if (cub->p_flag == 1)
		return (0);
	return (1);
}
