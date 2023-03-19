/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouizar <mouizar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 01:32:01 by mouizar           #+#    #+#             */
/*   Updated: 2023/03/19 03:25:52 by mouizar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlenn(const char	*s)
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

void	wallcontenth(t_cast_ray *casting, double *wall, t_data *d)
{
	if (casting->up)
		*wall = get_wall_cordinates(casting->next_x_intersect, \
		casting->next_y_intersect + (-1), d);
	else
		*wall = get_wall_cordinates(casting->next_x_intersect, \
		casting->next_y_intersect, d);
}

void	wallcontentv(t_cast_ray *casting, double *wall, t_data *d)
{
	if (casting->left)
		*wall = get_wall_cordinates(casting->next_vert_touch_x + \
		(-1), casting->next_vert_touch_y, d);
	else
		*wall = get_wall_cordinates(casting->next_vert_touch_x \
		, casting->next_vert_touch_y, d);
}
