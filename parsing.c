/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:27:03 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/01 22:47:07 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_floor_ceilling(t_cub3d *cub, char *str)
{
	int	i;
	int	j;

	if ((ft_strncmp(str, "F", 1) == 0 && cub->floor_rgb)
		|| (ft_strncmp(str, "C", 1) == 0 && cub->ceilling_rgb))
		return (0);
	i = 1;
	while (check_ws(str[i]))
		i++;
	j = i;
	while (ft_isprint(str[j]))
		j++;
	if (ft_strncmp(str, "F", 1) == 0 || ft_strncmp(str, "C", 1) == 0)
	{
		if (!ft_isdigit(str[i]))
			exit(write(2, "Invalide rgb\n", 14));
		if (ft_strncmp(str, "F", 1) == 0)
			cub->floor_rgb = ft_substr(str, i, j);
		else if (ft_strncmp(str, "C", 1) == 0)
			cub->ceilling_rgb = ft_substr(str, i, j);
	}
	if (cub->floor_rgb && cub->ceilling_rgb)
		i = (ft_check_rgb(cub->floor_rgb) && ft_check_rgb(cub->ceilling_rgb));
	return (i);
}

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

int	parsing_textur(t_cub3d *cub, char *str)
{
	int	i;

	i = 0;
	while (check_ws(*str))
		str++;
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || \
		!ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
	{
		i = ft_texture(cub, str);
	}
	else if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
		i = ft_floor_ceilling(cub, str);
	return (i);
}

void	ft_init_data(t_cub3d *cub, t_data *d)
{
	d->img_h = 0;
	d->img_w = 0;
	d->map_h = 640;
	d->map_w = 1728;
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->map_w, d->map_h, "Cub3D");
	d->t_no = mlx_xpm_file_to_image(d->mlx, cub->no_t, &d->img_w, &d->img_h);
	d->t_ea = mlx_xpm_file_to_image(d->mlx, cub->ea_t, &d->img_w, &d->img_h);
	d->t_we = mlx_xpm_file_to_image(d->mlx, cub->we_t, &d->img_w, &d->img_h);
	d->t_so = mlx_xpm_file_to_image(d->mlx, cub->so_t, &d->img_w, &d->img_h);
	if (!d->t_ea || !d->t_no || !d->t_so || !d->t_we)
		exit(write(2, "Invalide texture\n", 18));
}

void	parsing(t_cub3d *cub, t_data *d)
{
	int	i;

	i = 0;
	while (check_ws(*cub->infile[i]) || *cub->infile[i] == '\n')
		i++;
	while (cub->infile[i])
	{
		if (!(parsing_textur(cub, cub->infile[i])))
			exit(write(2, "Invalide data\n", 15));
		if ((cub->ceilling_rgb) && (cub->ea_t) && (cub->floor_rgb)
			&& (cub->no_t) && (cub->so_t) && (cub->we_t))
		{	
			i++;
			break ;
		}
		i++;
	}
	if (!parsing_map(cub, i))
		exit(write(2, "Invalide data\n", 15));
	ft_init_data(cub, d);
}
