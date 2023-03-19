/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:35:51 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 01:38:45 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_ray_init(t_data *data)
{
	int	i;

	i = 0;
	data->rays = ft_calloc(NUM_RAYS, sizeof(t_rays));
	while (i < NUM_RAYS)
	{
		data->rays[i].angle = data->player->rotationangle - \
		(data->rays->fov / 2);
		data->rays[i].fov = 60 * (PI / 180);
		data->rays[i].facing_down = 0;
		data->rays[i].facing_up = 0;
		data->rays[i].facing_right = 0;
		data->rays[i].facing_left = 0;
		data->rays[i].raynum = WIN_WIDHT;
		data->rays[i].washitve = 0;
		i++;
	}
}

int	ft_close_win(void)
{
	exit(0);
	return (0);
}

int	mapiswall(t_data *d, int x, int y)
{
	if (x < 0 || x > d->cub->map_whitd * TILE \
		|| y < 0 || y > d->cub->map_hight * TILE)
		return (1);
	if ((size_t)x < ft_strlen(d->cub->map[y]) && d->cub->map[y][x] == '1')
		return (1);
	return (0);
}

void	move_player(t_data *d)
{
	double	movestep;
	double	newx;
	double	newy;

	movestep = d->player->walk * d->player->movespeed;
	if (d->player->flg == 1)
	{
		newx = d->player->x \
		+ cos (d->player->rotationangle + PI / 2) * movestep;
		newy = d->player->y + sin(d->player->rotationangle + PI / 2) * movestep;
	}
	else
	{
		newx = d->player->x + cos (d->player->rotationangle) * movestep;
		newy = d->player->y + sin(d->player->rotationangle) * movestep;
	}
	if (!mapiswall(d, newx / TILE, d->player->y / TILE))
		d->player->x = newx;
	if (!mapiswall(d, d->player->x / TILE, newy / TILE))
		d->player->y = newy;
	d->player->rotationangle += d->player->turn * d->player->rot_speed ;
}
