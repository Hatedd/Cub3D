#include "../cub3d.h"

void	ft_ray_init(t_data *data)
{
	int	i;

	i = 0;
	data->rays = ft_calloc(NUM_RAYS, sizeof(t_rays));
	while (i < NUM_RAYS)
	{
		data->rays[i].angle = data->player->rotationangle - (FOV / 2);
		data->rays[i].fov = FOV;
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
void ft_draw_line(double x1, double y1, double x2, double y2, int color, t_data *data)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    // Determine which direction to step in
    int x_step = (dx > 0) ? 1 : -1;
    int y_step = (dy > 0) ? 1 : -1;

    // Determine the absolute values of dx and dy
    dx = fabs(dx);
    dy = fabs(dy);

    // Determine which distance is greater, and use it to determine the number of iterations
    double distance = (dx > dy) ? dx : dy;

    // Step along the line, drawing pixels as we go
    double x = x1;
    double y = y1;
    for (int i = 0; i <= distance; i++)
    {
        my_mlx_p_put(data, (int)x, (int)y, color);
        x += (dx / distance) * x_step;
        y += (dy / distance) * y_step;
    }
}

void	render_player(t_data *d)
{
	int		color;
	double	x0;
	double	y0;

	color = 0xFFFFFF;
	x0 = d->player->x;
	y0 = d->player->y;
		   ft_draw_square(d, color, x0, y0, 10);

	int endX = d->player->x + cos(d->player->rotationangle) * TILE;
    int endY = d->player->y + sin(d->player->rotationangle) * TILE;
    ft_draw_line(1.0 *d->player->x, 1.0 *d->player->y, endX, endY, color, d);
}

int	mapiswall(t_data *d, int x, int y)
{
	if (x < 0 || x > d->cub->map_whitd * TILE || y < 0 || y > d->cub->map_hight * TILE)
		return (1);
	if (d->cub->map[y][x] == '1')
		return (1);
	return (0);
}
int mapHasWallAt(double x, double y, t_data *d)
{
    int mapGridIndexX = floor(x);
    int mapGridIndexY = floor(y);

          if (x < 0 || x > TILE * d->cub->map_whitd|| y < 0 || y > d->cub->map_hight * TILE)
        return 1;
    if (mapGridIndexX < 0 || mapGridIndexX >= d->cub->map_whitd || mapGridIndexY < 0 || mapGridIndexY >= d->cub->map_hight) {
        return 1;
    }

    return d->cub->map[mapGridIndexY][mapGridIndexX] == '1';
}

void	move_player(t_data *d)
{
	double	movestep;
	double	newx;
	double	newy;

	movestep = d->player->walk * d->player->movespeed;
	if (d->player->flg == 1)
	{
		newx = d->player->x + cos (d->player->rotationangle + PI / 2) * movestep;
		newy = d->player->y + sin(d->player->rotationangle + PI / 2) * movestep;
	}
	else
	{
		newx = d->player->x + cos (d->player->rotationangle) * movestep;
		newy = d->player->y + sin(d->player->rotationangle) * movestep;
	// 	printf("down  >>>>>>>>>>>>>>>%d\n",d->rays->facing_down);
	// printf(" u .  >>>>>>>>>>>>>>>%d\n",d->rays->facing_up);
	// printf(" r . >>>>>>>>>>>>>>>%d\n",d->rays->facing_right);
	// printf("l . >>>>>>>>>>>>>>>%d\n",d->rays->facing_left);

	}
	// if (!mapiswall(d, newx / TILE, d->player->y / TILE))
	// 	d->player->x = newx;
	// if (!mapiswall(d, d->player->x / TILE, newy / TILE))
	// 	d->player->y = newy;
	if (!mapHasWallAt( newx / TILE, d->player->y / TILE,d))
		d->player->x = newx;
	if (!mapHasWallAt( d->player->x / TILE, newy / TILE, d))
		d->player->y = newy;
	d->player->rotationangle += d->player->turn * d->player->rot_speed ;
}
