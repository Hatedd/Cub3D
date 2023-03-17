/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:50:30 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/16 23:34:44 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	lastlen(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i == 0)
		exit(write(2, "Empty file\n", 12));
	i--;
	if (str[i] == '\n' && str[i - 1] == '\n' && i > 0)
		exit(write(2, "Erorr empty line in map\n", 25));
	while (check_ws(str[i]) && i > 0)
		i--;
	while (str[i] != '1' && i > 0)
	{
		i--;
		if (str[i] != '1' && str[i] != '\n' && str[i] != ' ' && i > 0)
			exit(write(2, "Invalide map\n", 14));
		else if (str[i] == '\n' && str[i - 1] == '\n' && i > 0)
			exit(write(2, "Invalide map\n", 14));
	}
	return (i);
}

void	check_empty(char *str, t_cub3d *cub)
{
	int	i;

	i = 0;
	while (check_ws(str[i]))
		i++;
	if (str[i] == '\0')
		exit(write(2, "Empty file\n", 12));
	else
		cub->valide = 1;
}

int	check_str2(char *str, int i, int len)
{
	while (i < len)
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			exit(write(2, "Erorr empty line in map\n", 25));
		i++;
	}
	return (i);
}

void	check_str(char *str, t_cub3d *cub)
{
	int	i;
	int	len;
	int	check;

	i = 0;
	len = lastlen(str);
	check = 0;
	check_empty(str, cub);
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E'\
			|| str[i] == 'F' || str[i] == 'C')
			check++;
		if (check > 7 && str[i] == '1')
		{
			i = check_str2(str, i, len);
			if (str[i] == '\0')
				break ;
		}
		i++;
	}
}

void	init_cub(char *file, t_cub3d *cub)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(write(2, "error in file or path given\n", 29));
	cub->no_t = NULL;
	cub->so_t = NULL;
	cub->we_t = NULL;
	cub->ea_t = NULL;
	cub->map = NULL;
	cub->floor_rgb = NULL;
	cub->ceilling_rgb = NULL;
	cub->p_flag = 0;
	cub->map_hight = 0;
	cub->map_whitd = 0;
	cub->m_flag = 0;
	cub->valide = 0;
	str = get_next_line(fd);
	if (!str)
		exit(write(2, "Error file\n", 12));
	check_str(str, cub);
	cub->infile = ft_split(str, '\n');
	close (fd);
}
