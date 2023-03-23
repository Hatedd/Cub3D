/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:36:04 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 21:24:40 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_key_press(int key_press, t_data *d)
{
	d->player->flg = 0;
	if (key_press == 13 || key_press == 126)
	{
		d->player->walk = +1;
	}
	else if (key_press == 1 || key_press == 125)
		d->player->walk = -1;
	else if (key_press == 0)
	{
		d->player->flg = 1;
		d->player->walk = -1;
	}
	else if (key_press == 2)
	{
		d->player->flg = 1;
		d->player->walk = 1;
	}
	else if (key_press == 124)
		d->player->turn = 1;
	else if (key_press == 123)
		d->player->turn = -1;
	else if (key_press == 53)
		exit(0);
	return (0);
}

int	ft_key_relase(int key_press, t_data *d)
{
	if (key_press == 13 || key_press == 126)
	{
		d->player->walk = 0;
	}
	else if (key_press == 1 || key_press == 125)
		d->player->walk = 0;
	else if (key_press == 0)
	{
		d->player->flg = 0;
		d->player->walk = 0;
	}
	else if (key_press == 2)
	{
		d->player->walk = 0;
		d->player->flg = 0;
	}
	else if (key_press == 124)
		d->player->turn = 0;
	else if (key_press == 123)
		d->player->turn = 0;
	return (0);
}

void	player_init(t_data *d)
{
	d->player->movespeed = 10;
	d->player->turn = 0;
	d->player->walk = 0;
	d->player->flg = 0;
	d->player->rot_speed = 5 * (PI / 180);
	if (d->cub->p_direction == 'W')
		d->player->rotationangle = 0;
	else if (d->cub->p_direction == 'N')
		d->player->rotationangle = PI / 2;
	else if (d->cub->p_direction == 'E')
		d->player->rotationangle = PI ;
	else
		d->player->rotationangle = (3 * PI) / 2;
	d->player->x = (d->cub->pos_x * TILE) + 32;
	d->player->y = (d->cub->pos_y * TILE) + 32;
	d->player->walk_speed = 5;
}

double	resize_radians(double angle)
{
	angle = fmod(angle, (2.0 * PI));
	if (angle < 0)
		angle = (2 * PI) + angle;
	return (angle);
}
