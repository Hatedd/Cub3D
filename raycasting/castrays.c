/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 02:41:46 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 03:27:55 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_assigne3d(t_treed *t)
{
	t->wall_strip_height = 0;
	t->wall_bottom_pixel = 0;
	t->wall_top_pixel = 0;
	t->pixel_index_y = 0;
	t->distance_top = 0;
	t->t_off_setx = 0;
	t->t_off_sety = 0;
	t->distance_projection_plane = 0;
	t->projected_wall_height = 0;
	t->perpendicular_hit_distance = 0;
}

void	ft_calculate_wall_render_values(t_data *data, int ray_index, t_treed *t)
{
	t->perpendicular_hit_distance = data->rays[ray_index].hit_dist * \
		cos(data->rays[ray_index].angle - data->player->rotationangle);
	t->distance_projection_plane = (WIN_WIDHT / 2) / tan(data->rays->fov / 2);
	t->projected_wall_height = (TILE / t->perpendicular_hit_distance) * \
		t->distance_projection_plane;
	t->wall_strip_height = (int)t->projected_wall_height;
	t->wall_top_pixel = (WIN_HIGHT / 2) - (t->wall_strip_height / 2);
	if (t->wall_top_pixel < 0)
		t->wall_top_pixel = 0;
	t->wall_bottom_pixel = (WIN_HIGHT / 2) + (t->wall_strip_height / 2);
	if (t->wall_bottom_pixel > WIN_HIGHT)
		t->wall_bottom_pixel = WIN_HIGHT;
}

void	ft_render3d(t_data *data, int ray_index)
{
	t_treed	t;

	ft_assigne3d(&t);
	ft_calculate_wall_render_values(data, ray_index, &t);
	t.pixel_index_y = t.wall_top_pixel;
	if (data->rays[ray_index].hit_vertical)
		t.t_off_setx = (int)(data->rays[ray_index].wallhit_y) % TILE;
	else
		t.t_off_setx = (int)(data->rays[ray_index].wallhit_x) % TILE;
	while (t.pixel_index_y < t.wall_bottom_pixel)
	{
		t.distance_top = t.pixel_index_y + \
		(t.wall_strip_height / 2) - (WIN_HIGHT / 2);
		t.t_off_sety = t.distance_top * ((float)TILE / t.wall_strip_height);
		my_mlx_p_put(data, ray_index, t.pixel_index_y, \
		my_mlx_texture(data, t.t_off_setx, t.t_off_sety, ray_index));
		t.pixel_index_y++;
	}
}

void	cast_ray(t_data *d, double ray_angle, int i)
{
	t_cast_ray	casting;

	casting.down = (ray_angle > 0 && ray_angle < PI);
	casting.up = (!casting.down);
	casting.right = (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
	casting.left = !casting.right;
	casting.hit_x = 0;
	casting.hit_y = 0;
	casting.hit_dist = 0;
	casting.is_hitvertical = 0;
	d->rays[i].facing_down = casting.down;
	d->rays[i].facing_up = !casting.down;
	d->rays[i].facing_right = casting.right;
	d->rays[i].facing_left = !casting.right;
	findhdist(d, ray_angle, i, &casting);
	findvdist(d, ray_angle, &casting);
	save_smallest_distance(&casting, i, d);
}

void	ft_castrays(t_data *d)
{
	double		ray_angle;
	int			i;

	i = -1;
	ray_angle = d->player->rotationangle - (d->rays->fov / 2);
	while (++i < NUM_RAYS)
	{
		ray_angle = resize_radians(ray_angle);
		d->rays[i].angle = ray_angle;
		cast_ray(d, ray_angle, i);
		ray_angle += d->rays->fov / NUM_RAYS;
		ft_render3d(d, i);
	}
}
