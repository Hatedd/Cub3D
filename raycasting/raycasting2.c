#include "../cub3d.h"

void	normalize_radians(double angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
		angle += (2 * PI);
}

double	hit_dis_bp(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	dbp(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	get_wall_cordinates(double x, double y, t_data *d)
{
	int	map_grid_x;
	int	map_grid_y;

	map_grid_x = floor(x / TILE);
	map_grid_y = floor(y / TILE);
	if (x < 0 || x > WIN_WIDHT || y < 0 || y > WIN_HIGHT)
		return (0);
	return (d->cub->map[map_grid_y][map_grid_x] - 48);
}

void	save_smallest_distance(t_cast_ray *casting, int i, t_data *d)
{
	casting->hit_dis_h = (casting->found_h_wall) ? hit_dis_bp(d->player->x, d->player->y, casting->horzhit_x, casting->horzhit_y) : INT_MAX;
	casting->hit_dis_ver = (casting->found_v_wall) ? hit_dis_bp(d->player->x, d->player->y, casting->verthit_x, casting->verthit_y) : INT_MAX;
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
	d->rays[i].hit_dist = casting->hit_dist;
	d->rays[i].wallhit_x = casting->hit_x;
	d->rays[i].wallhit_y = casting->hit_y;
	d->rays[i].hit_vertical = casting->is_hitvertical;
}
