#include "../cub3d.h"

void	find_v_wall(t_cast_ray *casting, t_data *d)
{
	double	wallcontent;

	while (casting->nextVertTouchX >= 0 && \
		casting->nextVertTouchX <= WIN_WIDHT & casting->nextVertTouchY >= 0 \
		&& casting->nextVertTouchY <= WIN_HIGHT)
	{
		if (casting->left)
			wallcontent = get_wall_cordinates(casting->nextVertTouchX + \
			(-1), casting->nextVertTouchY, d);
		else
			wallcontent = get_wall_cordinates(casting->nextVertTouchX, \
			casting->nextVertTouchY, d);
		if (wallcontent != 0)
		{
			casting->found_v_wall = 1;
			casting->verthit_x = casting->nextVertTouchX;
			casting->verthit_y = casting->nextVertTouchY;
			break ;
		}
		else
		{
			casting->nextVertTouchX += casting->deltax;
			casting->nextVertTouchY += casting->deltay;
		}
	}
}

void	find_v_dist(t_data *d, double ray_angle, int i, t_cast_ray *casting)
{
	casting->found_v_wall = 0;
	casting->verthit_x = 0;
	casting->verthit_y = 0;
	casting->x_intersect = floor(d->player->x / TILE) * TILE;
	if (casting->right)
		casting->x_intersect += TILE;
	casting->y_intersect = d->player->y + \
	(casting->x_intersect - d->player->x) * tan(ray_angle);
	casting->deltax = TILE;
	if (casting->left)
		casting->deltax *= -1;
	casting->deltay = TILE * tan(ray_angle);
	if (casting->up && casting->deltay > 0)
		casting->deltay *= -1;
	else if (casting->down && casting->deltay < 0)
		casting->deltay *= -1;
	casting->nextVertTouchX = casting->x_intersect;
	casting->nextVertTouchY = casting->y_intersect;
	find_v_wall(casting, d);
}

void	find_h_wall(t_cast_ray *casting, t_data *d)
{
	double	wallcontent;

	while (casting->next_x_intersect >= 0 && \
		casting->next_x_intersect <= WIN_WIDHT && \
		casting->next_y_intersect >= 0 && casting->next_y_intersect <= \
		WIN_HIGHT)
	{
		if (casting->up)
			wallcontent = get_wall_cordinates(casting->next_x_intersect, \
			casting->next_y_intersect + (-1), d);
		else
			wallcontent = get_wall_cordinates(casting->next_x_intersect, \
			casting->next_y_intersect, d);
		if (wallcontent != 0)
		{
		casting->found_h_wall = 1;
		casting->horzhit_x = casting->next_x_intersect;
		casting->horzhit_y = casting->next_y_intersect;
			break ;
		}
		else
		{
			casting->next_x_intersect += casting->deltax;
			casting->next_y_intersect += casting->deltay;
		}
	}
}

void	find_h_dist(t_data *d, double ray_angle, int i, t_cast_ray *casting)
{
	casting->found_h_wall = 0;
	casting->horzhit_x = 0;
	casting->horzhit_y = 0;
	d->rays[i].angle = ray_angle;
	casting->y_intersect = floor(d->player->y / TILE) * TILE;
	if (casting->down)
		casting->y_intersect +=  TILE;
	casting->x_intersect = d->player->x + \
	(casting->y_intersect - d->player->y) / tan(ray_angle);
	casting->deltay = TILE;
	if (casting->up)
		casting->deltay *= -1;
	else
		casting->deltay *= 1;
	casting->deltax = TILE / tan(ray_angle);
	if (casting->left && casting->deltax > 0)
		casting->deltax *= -1;
	else if (casting->right && casting->deltax < 0)
		casting->deltax *= -1;
	casting->next_x_intersect = casting->x_intersect;
	casting->next_y_intersect = casting->y_intersect;
	find_h_wall(casting, d);
}

void	cast_ray(t_data *d, double ray_angle, int i)
{
	t_cast_ray	casting;

	casting.down = ray_angle > 0 && ray_angle < PI;
	casting.up = !casting.down;
	casting.right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	casting.left = !casting.right;
	casting.hit_x = 0;
	casting.hit_y = 0;
	casting.hit_dist = 0;
	casting.is_hitvertical = 0;
	d->rays->facing_down = casting.down;
	d->rays->facing_up = casting.up;
	d->rays->facing_right = casting.right;
	d->rays->facing_left = casting.left;
	find_h_dist(d, ray_angle, i, &casting);
	find_v_dist(d, ray_angle, i, &casting);
	save_smallest_distance(&casting, i, d);
}
