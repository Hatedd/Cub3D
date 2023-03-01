/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 22:33:04 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/01 22:51:02 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_copy_map(t_cub3d *cub, int pos)
{
	int	i;

	i = 0;
	while (cub->infile[pos])
	{
		cub->map[i] = ft_strdup(cub->infile[pos]);
		i++;
		pos++;
	}
	cub->map[i] = 0;
	if (player_pos(cub))
		exit(write(2, "Invalide map\n", 14));
}

int	mat_len(t_cub3d *cub, int pos)
{
	int	i;

	i = 0;
	while (cub->infile[pos++])
		i++;
	return (i);
}

void	ft_updown(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_ws(str[i]) || str[i] == '1')
			i++;
		else
			exit(write(2, "Invalide map :(\n", 17));
	}
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

int	parsing_map(t_cub3d *cub, int pos)
{
	int	i;
	int	last;

	i = 0;
	cub->map_len = mat_len(cub, pos);
	last = cub->map_len - 1;
	if (!last)
		exit(write(2, "map not found\n", 15));
	cub->map = malloc(sizeof(char *) * (cub->map_len + 1));
	if (!cub->map)
		return (0);
	ft_copy_map(cub, pos);
	while (i < cub->map_len)
	{
		if (i == 0 || i == last)
			ft_updown(cub->map[i]);
		else
			ft_midline(cub->map[i]);
		i++;
	}
	return (1);
}
