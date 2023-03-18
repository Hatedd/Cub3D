#include "../cub3d.h"

void	my_mlx_p_put(t_data *data, int x, int y, int color)
{
	char	*d;

	if (x < 0 || x >= WIN_WIDHT || y < 0 || y >= WIN_HIGHT)
		return ;
	d = data->img->addr + (y * data->img->size + x * (data->img->bit_pp / 8));
	*(unsigned int *) d = color;
}

void	my_get_data_addr(t_data *data, int i)
{
	// if (data->rays[i].facing_down || data->rays[i].facing_up)
	// {
	// 	if (data->rays[i].facing_down)
	// 	{
	// 		data->address = mlx_get_data_addr(data->t_so, \
	// 			&data->bits_per_pixel, &data->line_len, &data->endian);
	// 	}
	// 	else
	// 	{
	// 		data->address = mlx_get_data_addr(data->t_no, \
	// 		&data->bits_per_pixel, &data->line_len, &data->endian);
	// 	}
	// }
	// if (data->rays[i].facing_right || data->rays[i].facing_left)
	// {
	// 	if (data->rays[i].facing_right)
	// 	{
	// 		data->address = mlx_get_data_addr(data->t_ea , \
	// 		&data->bits_per_pixel, &data->line_len, &data->endian);
	// 	}
	// 	else
	// 	{
	// 		data->address = mlx_get_data_addr(data->t_we, \
	// 		&data->bits_per_pixel, &data->line_len, &data->endian);
	// 	}
	// }

	if (!data->rays[i].hit_vertical)
	{
		if (data->rays[i].facing_up)
		{
			data->address = mlx_get_data_addr(data->t_so, \
				&data->bits_per_pixel, &data->line_len, &data->endian);
		}
		else
		{
			data->address = mlx_get_data_addr(data->t_no, \
				&data->bits_per_pixel, &data->line_len, &data->endian);
		}
	}
	else
	{
		if (data->rays[i].facing_right)
		{
			data->address = mlx_get_data_addr(data->t_we , \
			&data->bits_per_pixel, &data->line_len, &data->endian);
		}
		else
		{
			data->address = mlx_get_data_addr(data->t_ea, \
			&data->bits_per_pixel, &data->line_len, &data->endian);
		}
	}
}

int	raycasting(t_data *d)
{
	int	i;

	if (!d->img->img)
	{
		d->img->img = mlx_new_image(d->mlx, WIN_WIDHT, WIN_HIGHT);
		d->img->addr = mlx_get_data_addr(d->img->img, \
		&d->img->bit_pp, &d->img->size, &d->img->end);
	}
	if (d->flag == 1)
		mlx_clear_window(d->mlx, d->win);
	// render_player(d);
	move_player(d);
	render_floor_roof(d);
	ft_castrays(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img->img, 0, 0);
	mlx_destroy_image(d->mlx, d->img->img);
	d->img->img = 0;
	d->flag = 1;
	return (0);
}
