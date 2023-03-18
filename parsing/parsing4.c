/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:07:06 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/18 03:17:42 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_texture(t_cub3d *cub, char *str)
{
	int	i;
	int	j;

	if ((ft_strncmp(str, "NO", 2) == 0 && cub->no_t)
		|| (ft_strncmp(str, "SO", 2) == 0 && cub->so_t)
		|| (ft_strncmp(str, "WE", 2) == 0 && cub->we_t)
		|| (ft_strncmp(str, "EA", 2) == 0 && cub->ea_t))
		return (0);
	i = 2;
	while (check_ws(str[i]))
		i++;
	j = i;
	while (ft_isprint(*str + j) && !check_ws(*str + j))
		j++;
	if (ft_strncmp(str, "NO", 2) == 0)
		cub->no_t = ft_substr(str, i, j);
	else if (ft_strncmp(str, "SO", 2) == 0)
		cub->so_t = ft_substr(str, i, j);
	else if (ft_strncmp(str, "WE", 2) == 0)
		cub->we_t = ft_substr(str, i, j);
	else if (ft_strncmp(str, "EA", 2) == 0)
		cub->ea_t = ft_substr(str, i, j);
	return (1);
}

void	ft_midline(char *str)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = ft_strlen(str);
	while (check_ws(str[i]))
		i++;
	if (str[i] == '\0')
		return ;
	if (str[i] != '1' || str[line_len - 1] != '1')
	{
		while (check_ws(str[line_len - 1]))
			line_len--;
		if (str[line_len - 1] != '1' || str[i] != '1')
			exit(write(2, "Invalide map :(\n", 17));
	}
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && \
			str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && str[i] != ' ')
			exit(write(2, "Invalide map :(\n", 17));
		i++;
	}
}

int	get_rgb_from_string(char *line)
{
	char	**components;
	int		rgb[3];
	int		i;

	i = -1;
	components = ft_split(line, ',');
	while (++i < 3)
	{
		rgb[i] = ft_atoi(components[i]);
	}
	return ((rgb[0] << 16 | rgb[1] << 8) | rgb[2]);
}

void	render_floor_roof(t_data *data)
{
	data->floor_color = get_rgb_from_string(data->cub->floor_rgb);
	data->ceiling_color = get_rgb_from_string(data->cub->ceilling_rgb);
	data->row = 0;
	while (data->row < WIN_HIGHT / 2)
	{
		data->col = 0;
		while (data->col < WIN_WIDHT)
		{
			my_mlx_p_put(data, data->col, data->row, data->ceiling_color);
			data->col++;
		}
		data->row++;
	}
	data->row = WIN_HIGHT / 2;
	while (data->row < WIN_HIGHT)
	{
		data->col = 0;
		while (data->col < WIN_WIDHT)
		{
			my_mlx_p_put(data, data->col, data->row, data->floor_color);
			data->col++;
		}
		data->row++;
	}
}

void	creat_win(t_data *data, t_img *img)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDHT, WIN_HIGHT, "Cub3Dii");
	img->img = mlx_new_image(data->mlx, WIN_WIDHT, WIN_HIGHT);
	img->addr = mlx_get_data_addr(data->img->img, &img->bit_pp, \
		&img->size, &img->end);
	data->t_no = mlx_xpm_file_to_image(data->mlx, data->cub->no_t, \
		&data->img_w, &data->img_h);
	data->t_ea = mlx_xpm_file_to_image(data->mlx, data->cub->ea_t, \
		&data->img_w, &data->img_h);
	data->t_so = mlx_xpm_file_to_image(data->mlx, data->cub->so_t, \
		&data->img_w, &data->img_h);
	data->t_we = mlx_xpm_file_to_image(data->mlx, data->cub->we_t, \
		&data->img_w, &data->img_h);
	if (!data->t_so || !data->t_no || !data->t_ea || !data->t_we)
		exit(write(2, "Error xpm\n", 11));
}
