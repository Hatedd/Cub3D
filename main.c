/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamedouizar <mohamedouizar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:21:06 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/07 05:2 by mohamedouiz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_freee(char	**sr)
{
	int	i;

	i = 0;
	while (sr[i])
	{
		free(sr[i]);
		i++;
	}
	free(sr);
}

int	check_ws(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
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

int	main(int ac, char **av)
{
	t_cub3d	*cub;
	t_data	d;
	t_img	img;
	int		len;

	cub = malloc(sizeof(t_cub3d));
	if (ac == 2)
	{
		len = ft_strlen(av[1]) - 4;
		if (ft_strncmp(&av[1][len], ".cub", 4))
			exit(write(2, "Invalide file name\n", 20));
		init_cub(av[1], cub);
		parsing(cub);
		ft_init_data(cub, &d, &img);
		creat_win(&d, &img);
		player_init(&d);
		ft_ray_init(&d);
		mlx_hook(d.win, 2, 1L << 0, ft_key_press, &d);
		mlx_hook(d.win, 3, 1L << 1, ft_key_relase, &d);
		mlx_loop_hook(d.mlx, raycasting, &d);
		mlx_loop(d.mlx);
	}
	return (0);
}
