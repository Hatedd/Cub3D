/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:00:56 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/17 00:23:51 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	img_init(t_data *data)
{
	data->endian = 0;
	data->bits_per_pixel = 0;
	data->line_len = 0;
	data->address = NULL;
}

int	ft_map_width(char **s)
{
	int	l;
	int	index;

	index = 0;
	l = 0;
	while (s[index])
	{
		if ((size_t)l < ft_strlen(s[index]))
			l = ft_strlen(s[index]);
		index++;
	}
	return (l);
}

int	ft_map_hight(char **s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

void	ft_init_img(t_img *img)
{
	img->addr = NULL;
	img->bit_pp = 0;
	img->end = 0;
	img->size = 0;
}

void	ft_init_data(t_cub3d *cub, t_data *d, t_img *img)
{
	d->flag = 0;
	ft_init_img(img);
	d->img = img;
	cub->map_hight = ft_map_hight(cub->map);
	cub->map_whitd = ft_map_width(cub->map);
	d->player = malloc(sizeof(t_player));
	d->cub = cub;
}
