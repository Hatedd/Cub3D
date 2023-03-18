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

int	is_valid_move(double x, double y)
{
	if (x < 0 || x >= WIN_WIDHT || y < 0 || y >= WIN_HIGHT)
		return (0);
	return (1);
}

void	player_init(t_data *d)
{
	d->player->movespeed = 5;
	d->player->turn = 0;
	d->player->walk = 0;
	d->player->flg = 0;
	d->player->rot_speed = 2 * (PI / 180);
	if (d->cub->p_direction == 'W')
		d->player->rotationangle = 180 *( PI / 2);
	else if (d->cub->p_direction == 'N')
		d->player->rotationangle = 90 *( PI / 2);
	else if (d->cub->p_direction == 'E')
		d->player->rotationangle = 0 *( PI / 2);
	else
		d->player->rotationangle = 270 *( PI / 2);
	d->player->x =	(d->cub->pos_x * TILE) + 32;
	d->player->y = (d->cub->pos_y * TILE) + 32;
	d->player->walk_speed = 5;
}
