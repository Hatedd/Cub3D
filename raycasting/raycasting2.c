/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:22:52 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 02:34:16 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	normalize_radians(double angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
}

double	hit_dis_bp(double x1x, double y1x, double x2x, double y2x)
{
	return (sqrt((x2x - x1x) * (x2x - x1x) + (y2x - y1x) * (y2x - y1x)));
}

int	get_wall_cordinates(double x, double y, t_data *d)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = floor(x / TILE);
	map_grid_y = floor(y / TILE);
	if (map_grid_y < 0 || map_grid_y >= d->cub->map_hight || map_grid_x < 0
		|| map_grid_x >= ft_strlenn(d->cub->map[map_grid_y]))
		return (0);
	return (d->cub->map[map_grid_y][map_grid_x] - 48);
}

void	save_ray_dist(t_data *d, t_cast_ray *casting, int i)
{
	d->rays[i].hit_dist = casting->hit_dist;
	d->rays[i].wallhit_x = casting->hit_x;
	d->rays[i].wallhit_y = casting->hit_y;
	d->rays[i].hit_vertical = casting->is_hitvertical;
}

void	save_smallest_distance(t_cast_ray *casting, int i, t_data *d)
{
	casting->hit_dis_h = INT_MAX;
	casting->hit_dis_ver = INT_MAX;
	if (casting->found_h_wall)
		casting->hit_dis_h = hit_dis_bp(d->player->x, d->player->y, \
		casting->horzhit_x, casting->horzhit_y);
	if (casting->found_v_wall)
		casting->hit_dis_ver = hit_dis_bp(d->player->x, d->player->y, \
		casting->verthit_x, casting->verthit_y);
	if (casting->hit_dis_ver < casting->hit_dis_h)
	{
		casting->hit_x = casting->verthit_x;
		casting->hit_y = casting->verthit_y;
		casting->hit_dist = casting->hit_dis_ver;
		casting->is_hitvertical = 1;
	}
	else
	{
		casting->hit_x = casting->horzhit_x;
		casting->hit_y = casting->horzhit_y;
		casting->hit_dist = casting->hit_dis_h;
		casting->is_hitvertical = 0;
	}
	save_ray_dist(d, casting, i);
}
