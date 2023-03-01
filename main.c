/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:21:06 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/01 22:44:53 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_walls_check(t_cub3d *cub, int i, int j, int flag)
{
	int	c;

	c = 0;
	while (cub->map[i + c][j] == ' ')
	{
		if (cub->m_flag)
			if (cub->map[i + c][j - 1] != '1')
				exit(write(2, "Map walls error\n", 17));
		if (flag)
			c--;
		else
			c++;
		if (cub->map[i + c][j] == '1')
		{
			if (cub->m_flag)
				if (cub->map[i + c][j - 1] != '1')
					exit(write(2, "Map walls error\n", 17));
			cub->m_flag = 0;
			break ;
		}
		else if (cub->map[i + c][j] != '1' && cub->map[i + c][j] != ' ')
			exit(write(2, "Map walls error\n", 17));
	}
}

void	ft_mid_help(t_cub3d *cub, int i, size_t j)
{
	if ((j >= ft_strlen(cub->map[i - 1]) || \
		j >= ft_strlen(cub->map[i + 1])) && cub->map[i + 1])
		exit(write(2, "Invalide map\n", 14));
	if (j == 0)
		exit(write(2, "Invalide map\n", 14));
	if ((cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == ' ' || \
		cub->map[i][j - 1] == ' ' || cub->map[i][j + 1] == ' ') && \
		cub->map[i][j + 1])
		exit(write(2, "Invalide map\n", 14));
}

int	main(int ac, char **av)
{
	t_cub3d	cub;
	t_data	d;
	int		len;
	int		i;

	i = 0;
	if (ac == 2)
	{
		len = ft_strlen(av[1]) - 4;
		if (ft_strncmp(&av[1][len], ".cub", 4))
			exit(write(2, "Invalide file name\n", 20));
		init_cub(av[1], &cub);
		parsing(&cub, &d);
		while (cub.map[i])
		{
			printf("%s\n", cub.map[i]);
			i++;
		}
		mlx_loop(d.mlx);
	}
	return (0);
}
