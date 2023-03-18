#include "../cub3d.h"

unsigned int	my_mlx_texture(t_data *data, int x, int y, int i)
{
	char	*dst;

	my_get_data_addr(data, i);
	dst = data->address + (y * data->line_len + x * \
	(data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_render3d(t_data *data, int ray_index)
{
	int		wall_strip_height;
	int		wall_bottom_pixel;
	int		wall_top_pixel;
	int		pixel_index_y;
	int		distance_top;
	int		t_off_setx;
	int		t_off_sety;
	double	distance_projection_plane;
	double	projected_wall_height;
	double	perpendicular_hit_distance;

	perpendicular_hit_distance = data->rays[ray_index].hit_dist * \
	cos(data->rays[ray_index].angle - data->player->rotationangle);
	distance_projection_plane = (WIN_WIDHT / 2) / tan(data->rays->fov / 2);
	projected_wall_height = (TILE / perpendicular_hit_distance) * \
	distance_projection_plane;
	wall_strip_height = (int)projected_wall_height;
	wall_top_pixel = (WIN_HIGHT / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (WIN_HIGHT / 2) + (wall_strip_height / 2);
	if (wall_bottom_pixel > WIN_HIGHT)
		wall_bottom_pixel = WIN_HIGHT;
	pixel_index_y = wall_top_pixel;
	if (data->rays[ray_index].hit_vertical)
		t_off_setx = (int)(data->rays[ray_index].wallhit_y) % TILE;
	else
		t_off_setx = (int)(data->rays[ray_index].wallhit_x) % TILE;
	while (pixel_index_y < wall_bottom_pixel)
	{
		distance_top = pixel_index_y + \
		(wall_strip_height / 2) - (WIN_HIGHT / 2);
		t_off_sety = distance_top * ((float)TILE / wall_strip_height);
		my_mlx_p_put(data, ray_index, pixel_index_y, \
		my_mlx_texture(data, t_off_setx, t_off_sety, ray_index));
		// my_mlx_p_put(data, ray_index, pixel_index_y, 0x0000F0);
		pixel_index_y++;
	}
}

double	resize_radians(double angle)
{
	angle = fmod(angle, (2.0 * PI));
	if (angle < 0)
		angle = (2 * PI) + angle;
	return (angle);
}

void	ft_castrays(t_data *d)
{
	t_cast_ray	casting;
	double		ray_angle;
	int			i;

	i = -1;
	ray_angle = d->player->rotationangle - (FOV / 2);
	while (++i < NUM_RAYS)
	{
		ray_angle = resize_radians(ray_angle);
		d->rays[i].angle = ray_angle;
		cast_ray(d, ray_angle, i);
		ray_angle += FOV / NUM_RAYS;
		ft_render3d(d, i);
	}
}
