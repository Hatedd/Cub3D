#include "../cub3d.h"

void	ft_draw_square(t_data *data, int color, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < TILE)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_p_put(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_border(t_data *d, int i, int j, int color)
{
	int	size;
	int	x;
	int	y;

	size = 64;
	x = i * size;
	while (x < i * size + size)
	{
		my_mlx_p_put(d, j * size, x, color);
		my_mlx_p_put(d, (j + 1) * size - 1, x, color);
		x++;
	}
	y = j * size;
	while (y < j * size + size)
	{
		my_mlx_p_put(d, y, i * size, color);
		my_mlx_p_put(d, y, (i + 1) * size - 1, color);
		y++;
	}
}

int	ft_strlenn(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	check_next_empty(int i, int j, t_data *d)
{
	if (i == 0 || j == 0 || i == d->cub->map_len - 1 || \
		j == ft_strlenn(d->cub->map[i]) - 1 || d->cub->map[i - 1][j] == '0' \
		|| d->cub->map[i][j - 1] == '0' || d->cub->map[i + 1][j] == '0' || \
		d->cub->map[i][j + 1] == '0')
		return (1);
	return (0);
}

void	render_map(t_data *data)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 64;
	while (i < data->cub->map_len)
	{
		j = 0;
		while (j < ft_strlenn(data->cub->map[i]))
		{
			if (data->cub->map[i][j] == '1')
			{
				if (check_next_empty(i, j, data) == 1)
					draw_border(data, i, j, 0x0000F0);
				else
					ft_draw_square(data, 0xFFFF00, j * size, i * size, size);
			}
			else if (data->cub->map[i][j] == '0')
			{
				ft_draw_square(data, 0x00FF00, j * size, i * size, size);
				draw_border(data, i, j, 0x0000F0);
			}
			j++;
		}
		i++;
	}
}
