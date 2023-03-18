/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:35:22 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/18 02:52:07 by yobenali         ###   ########.fr       */
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
			break;
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
		if (ft_strchr(cub->map[i], 'E'))
			player_dire(cub, i) && cub->p_flag++;
		if (ft_strchr(cub->map[i], 'S'))
			player_dire(cub, i) && cub->p_flag++;
		if (ft_strchr(cub->map[i], 'N'))
			player_dire(cub, i) && cub->p_flag++;
		if (ft_strchr(cub->map[i], 'W'))
			player_dire(cub, i) && cub->p_flag++;
		i++;
	}
	ft_chflood(cub);
	if (cub->p_flag == 1)
		return (0);
	return (1);
}

void	ft_copy_map(t_cub3d *cub, int pos)
{
	int	i;

	i = 0;
	while (cub->infile[pos])
	{
		cub->map[i] = ft_strdup(cub->infile[pos]);
		i++;
		pos++;
	}
	cub->map[i] = 0;
	if (player_pos(cub))
		exit(write(2, "Invalide map\n", 14));
}

int	parsing_textur(t_cub3d *cub, char *str)
{
	int	i;

	i = 0;
	while (check_ws(*str))
		str++;
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || \
		!ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
	{
		i = ft_texture(cub, str);
	}
	else if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
		i = ft_floor_ceilling(cub, str);
	return (i);
}

int	parsing_map(t_cub3d *cub, int pos)
{
	int	i;
	int	last;

	i = 0;
	cub->map_len = mat_len(cub, pos);
	last = cub->map_len - 1;
	if (!last)
		exit(write(2, "map not found\n", 15));
	cub->map = malloc(sizeof(char *) * (cub->map_len + 1));
	if (!cub->map)
		return (0);
	ft_copy_map(cub, pos);
	while (i < cub->map_len)
	{
		if (i == 0 || i == last)
			ft_updown(cub->map[i]);
		else
			ft_midline(cub->map[i]);
		i++;
	}
	return (1);
}

void	parsing(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (check_ws(cub->infile[i][0]) && cub->infile[i][0] == '\n' )
		i++;
	while (cub->infile[i])
	{
		if (!(parsing_textur(cub, cub->infile[i])))
			exit(write(2, "Invalide data\n", 15));
		if ((cub->ceilling_rgb) && (cub->ea_t) && (cub->floor_rgb)
			&& (cub->no_t) && (cub->so_t) && (cub->we_t))
		{	
			i++;
			break ;
		}
		i++;
	}
	if (!parsing_map(cub, i))
		exit(write(2, "Invalide data\n", 15));
}
