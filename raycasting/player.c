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

void	render_player(t_data *d)
{
	int		color;
	double	x0;
	double	y0;

	color = 0xFFFFFF;
	x0 = d->player->x;
	y0 = d->player->y;
}

int	mapiswall(t_data *d, int x, int y)
{
	if (x < 0 || x > d->cub->map_whitd * TILE || y < 0 || y > 10 * TILE)
		return (1);
	if (d->cub->map[y][x] == '1')
		return (1);
	return (0);
}

void	move_player(t_data *d)
{
	double	movestep;
	double	newx;
	double	newy;

	d->player->rotationangle += d->player->turn * d->player->rot_speed ;
	movestep = d->player->walk * d->player->movespeed;
	newx = d->player->x + cos (d->player->rotationangle) * movestep;
	newy = d->player->y + sin(d->player->rotationangle) * movestep;
	if (!mapiswall(d, newx / TILE, d->player->y / TILE))
		d->player->x = newx;
	if (!mapiswall(d, d->player->x / TILE, newy / TILE))
		d->player->y = newy;
}
