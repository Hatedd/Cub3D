/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castrays2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:50:12 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 03:29:17 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_v_wall(t_cast_ray *casting, t_data *d)
{
	double	wallcontent;

	wallcontent = 0;
	while (casting->next_vert_touch_y >= 0 && \
			casting->next_vert_touch_y <= d->cub->map_hight * TILE && \
				casting->next_vert_touch_x >= 0 && \
					casting->next_vert_touch_x <= d->cub->map_whitd * TILE)
	{
		wallcontentv(casting, &wallcontent, d);
		if (wallcontent != 0)
		{
			casting->found_v_wall = 1;
			casting->verthit_x = casting->next_vert_touch_x;
			casting->verthit_y = casting->next_vert_touch_y;
			break ;
		}
		else
		{
			casting->next_vert_touch_x += casting->deltax;
			casting->next_vert_touch_y += casting->deltay;
		}
	}
}

void	findvdist(t_data *d, double ray_angle, t_cast_ray *cst)
{
	cst->found_v_wall = 0;
	cst->verthit_x = 0;
	cst->verthit_y = 0;
	cst->x_intersect = floor(d->player->x / TILE) * TILE;
	if (cst->right)
		cst->x_intersect += TILE;
	cst->y_intersect = d->player->y + \
	(cst->x_intersect - d->player->x) * tan(ray_angle);
	cst->deltax = TILE;
	if (cst->left)
		cst->deltax *= -1;
	cst->deltay = TILE * tan(ray_angle);
	if (cst->up && cst->deltay > 0)
		cst->deltay *= -1;
	else if (cst->down && cst->deltay < 0)
		cst->deltay *= -1;
	cst->next_vert_touch_x = cst->x_intersect;
	cst->next_vert_touch_y = cst->y_intersect;
	find_v_wall(cst, d);
}

void	find_h_wall(t_cast_ray *casting, t_data *d)
{
	double	wallcontent;

	wallcontent = 0;
	while (casting->next_y_intersect >= 0 && \
			casting->next_y_intersect <= d->cub->map_hight * TILE && \
				casting->next_x_intersect >= 0 && \
					casting->next_x_intersect <= d->cub->map_whitd * TILE)
	{
		wallcontenth(casting, &wallcontent, d);
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

void	findhdist(t_data *d, double ray_angle, int i, t_cast_ray *cst)
{
	cst->found_h_wall = 0;
	cst->horzhit_x = 0;
	cst->horzhit_y = 0;
	d->rays[i].angle = ray_angle;
	cst->y_intersect = floor(d->player->y / TILE) * TILE;
	if (cst->down)
		cst->y_intersect += TILE;
	cst->x_intersect = d->player->x + \
	(cst->y_intersect - d->player->y) / tan(ray_angle);
	cst->deltay = TILE;
	if (cst->up)
		cst->deltay *= -1;
	else
		cst->deltay *= 1;
	cst->deltax = TILE / tan(ray_angle);
	if (cst->left && cst->deltax > 0)
		cst->deltax *= -1;
	else if (cst->right && cst->deltax < 0)
		cst->deltax *= -1;
	cst->next_x_intersect = cst->x_intersect;
	cst->next_y_intersect = cst->y_intersect;
	find_h_wall(cst, d);
}
