/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:21:06 by yobenali          #+#    #+#             */
/*   Updated: 2023/02/20 22:25:47 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_myatoi(const char *str)
{
	int				i;
	unsigned long	r;

	i = 0;
	r = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		i++;
	}
	if (str[i] == '-' || str[i] != '\0')
		exit(write(2, "Invalide rgb\n", 14));
	return (r);
}

int	check_ws(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	ft_check_rgb(char *rgb)
{
	int		i;
	int		len;
	int		ccheck;
	char	**tmp;

	len = 2;
	ccheck = 0;
	while (check_ws(rgb[len]))
		len++;
	tmp = ft_split(rgb + len, ',');
	while (rgb[len])
	{
		i = 0;
		while (ft_isdigit(rgb[len]) && rgb[len])
		{
			len++;
			i++;
		}
		if (rgb[len] == ',' && rgb[len])
		{
			len++;
			i = 0;
			ccheck++;
		}
		if (!ft_isdigit(rgb[len]) && rgb[len] != ',' && rgb[len])
			exit(write(2, "Invalide rgb data\n", 19));
		if ((ccheck != 2 || i > 2) && !rgb[len])
			exit(write(2, "Invalide rgb data\n", 19));
	}
	i = 0;
	while (tmp[i] != NULL)
	{
		len = ft_myatoi(tmp[i]);
		if (len > 255)
			return (0);
		i++;
	}
	ft_free(tmp);
	return (1);
}


int	ft_floor_ceilling(t_cub3d *cub, char *str)
{
	int	i;
	int	j;
	
	if ((ft_strncmp(str, "F", 1) == 0 && cub->floor_rgb)
		|| (ft_strncmp(str, "C", 1) == 0 && cub->ceilling_rgb))
		return (0);
	i = 1;
	while (check_ws(*str + i))
		i++;
	j = i;
	while (ft_isprint(*str + j))
		j++;
	if (ft_strncmp(str, "F", 1) == 0)
		cub->floor_rgb = ft_substr(str, i, j);
	else if (ft_strncmp(str, "C", 1) == 0)
		cub->ceilling_rgb = ft_substr(str, i, j);
	if (cub->ceilling_rgb)
		return (ft_check_rgb(cub->ceilling_rgb));
	else if (cub->floor_rgb)
		return (ft_check_rgb(cub->floor_rgb));
	return (1);
}

int	ft_texture(t_cub3d *cub, char *str)
{
	int	i;
	int	j;

	if ((ft_strncmp(str, "NO", 2) == 0 && cub->no_texture)
		|| (ft_strncmp(str, "SO", 2) == 0 && cub->so_texture)
		|| (ft_strncmp(str, "WE", 2) == 0 && cub->we_texture)
		|| (ft_strncmp(str, "EA", 2) == 0 && cub->ea_texture))
		return (0);
	i = 2;
	while (check_ws(str[i]))
		i++;
	j = i;
	while (ft_isprint(*str + j) && !check_ws(*str +j))
		j++;
	if (ft_strncmp(str, "NO", 2) == 0)
		cub->no_texture = ft_substr(str, i, j);
	else if (ft_strncmp(str, "SO", 2) == 0)
		cub->so_texture = ft_substr(str, i, j);
	else if (ft_strncmp(str, "WE", 2) == 0)
		cub->we_texture = ft_substr(str, i, j);
	else if (ft_strncmp(str, "EA", 2) == 0)
		cub->ea_texture = ft_substr(str, i, j);
	return (1);
}

int	parsing_textur(t_cub3d *cub, char *str)
{
	int	i;

	i = 0;
	while (check_ws(*str))
		str++;
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
	{
		i = ft_texture(cub, str);
	}
	else if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
		i = ft_floor_ceilling(cub, str);
	return (i);
}

void	ft_ending(t_cub3d *cub, int i, int j)
{
	int	len;
	int	checker;

	len = ft_strlen(cub->map[i]);
	while (check_ws(cub->map[i][len - 1]))
		len--;
	while (check_ws(cub->map[i][j]))
		j++;
	while (j < len)
	{
		checker = 0;
		while (cub->map[i + checker][j] == ' ')
		{
			if (cub->m_flag)
				if (cub->map[i + checker][j - 1] != '1')
					exit(write(2, "Map walls error\n", 17));
			checker--;
			if (cub->map[i + checker][j] == '1')
			{
				if (cub->m_flag)
					if (cub->map[i + checker][j - 1] != '1')
						exit(write(2, "Map walls error\n", 17));
				cub->m_flag = 0;
				break;
			}
			else if (cub->map[i + checker][j] != '1' && cub->map[i + checker][j] != ' ')
				exit(write(2, "Map walls error\n", 17));
		}
		j++;
	}
}

void	ft_beginning(t_cub3d *cub, int i, int j)
{
	int	len;
	int	checker;

	len = ft_strlen(cub->map[i]);
	while (check_ws(cub->map[i][len - 1]))
		len--;
	while (check_ws(cub->map[i][j]))
		j++;
	while (j < len)
	{
		checker = 0;
		while (cub->map[i + checker][j] == ' ')
		{
			if (cub->m_flag)
				if (cub->map[i + checker][j - 1] != '1')
					exit(write(2, "Map walls error\n", 17));
			checker++;
			if (cub->map[i + checker][j] == '1')
			{
				if (cub->m_flag)
					if (cub->map[i + checker][j - 1] != '1')
						exit(write(2, "Map walls error\n", 17));
				cub->m_flag = 0;
				break;
			}
			else if (cub->map[i + checker][j] != '1' && cub->map[i + checker][j] != ' ')
				exit(write(2, "Map walls error\n", 17));
		}
		j++;
	}
}

void	ft_mid(t_cub3d *cub, int i, int j)
{
	int		len;
	char	c;
	
	len = ft_strlen(cub->map[i]);
	while (check_ws(cub->map[i][len - 1]))
		len--;
	while (check_ws(cub->map[i][j]))
		j++;
	while (j < len)
	{
		c = cub->map[i][j];
		if (c == '0' || c == 'E' || c == 'W' || c == 'S' || c == 'N')
		{
			if ((size_t)j > ft_strlen(cub->map[i - 1]) || (size_t)j > ft_strlen(cub->map[i + 1]))
				exit(write(2, "Invalide map\n", 19));
			if ((cub->map[i - 1][j] == ' ' || cub->map[i + 1][j] == ' ' || \
				cub->map[i][j - 1] == ' ' || cub->map[i][j + 1] == ' ') && \
				cub->map[i][j + 1])
				exit(write(2, "Invalide map\n", 14));
		}
		j++;
	}
}

void	ft_chflood(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	cub->m_flag = 1;
	while (i <	cub->map_len)
	{
		j = 0;
		if (i == 0)
			ft_beginning(cub, i, j);
		else if (i == cub->map_len - 1)
			ft_ending(cub, i, j);
		else
			ft_mid(cub, i, j);
		i++;
	}
}

int	player_pos(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < cub->map_len)
	{
		if (ft_strchr(cub->map[i], 'E'))
			cub->p_flag++;
		else if (ft_strchr(cub->map[i], 'S'))
			cub->p_flag++;
		else if (ft_strchr(cub->map[i], 'N'))
			cub->p_flag++;
		else if (ft_strchr(cub->map[i], 'W'))
			cub->p_flag++;
		i++;
	}
	ft_chflood(cub);
	if (cub->p_flag == 1)
		return (0);
	return(1);
}

void ft_copy_map(t_cub3d *cub, int pos)
{
	int i;
	i = 0;
	while (cub->infile[pos])
	{
		cub->map[i] = ft_strdup(cub->infile[pos]);
		i++;
		pos++;
	}
	if (player_pos(cub))
		exit(write(2, "Invalide map\n", 14));
}

int mat_len(t_cub3d *cub, int pos)
{
	int i;

	i = 0;
	while (cub->infile[pos++])
		i++;
	return (i);
}

void	ft_updown(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_ws(str[i]) || str[i] == '1')
			i++;
		else
		{
			exit(write(2, "Invalide map :(\n", 17));
		}
	}
}

void    ft_midline(char *str)
{
	int i;
	int line_len;

	i = 0;
	line_len = ft_strlen(str);
	while(check_ws(str[i]))
		i++;
	if (str[i] != '1' || str[line_len - 1] != '1')
	{
		while (check_ws(str[line_len - 1]))
			line_len--;
		if (str[line_len - 1] != '1' || str[i] != '1')
			exit(write(2, "Invalide map :(\n", 17));
	}
	while(str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && str[i] != ' ')
		{
			exit(write(2, "Invalide map :(\n", 17));
		}
		i++;
	}
}

int parsing_map(t_cub3d *cub, int pos)
{
	int i;
	int last;

	i = 0;
	cub->map_len = mat_len(cub, pos);
	last = cub->map_len - 1;
	if (!last)
		exit(write(2, "map not found\n", 15));
	cub->map = malloc(sizeof(char *) * cub->map_len + 1);
	if (!cub->map)
	    return (0);
	ft_copy_map(cub, pos);
	while (i < cub->map_len)
	{
		if (i == 0 || i == last)
			ft_updown(cub->map[i]);
		// else if (i == last)
		// 	return (1);
		else
			ft_midline(cub->map[i]);
		i++;
	}
	return (1);
}

void	ft_init_data(t_cub3d *cub, t_data *data)
{
	data->img_h = 0;
	data->img_w = 0;
	data->map_h = 640;
	data->map_w = 1728;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_w, data->map_h, "Cub3D");
	data->t_no = mlx_xpm_file_to_image(data->mlx, cub->no_texture, &data->img_w, &data->img_h);
	data->t_ea = mlx_xpm_file_to_image(data->mlx, cub->ea_texture, &data->img_w, &data->img_h);
	data->t_we = mlx_xpm_file_to_image(data->mlx, cub->we_texture, &data->img_w, &data->img_h);
	data->t_so = mlx_xpm_file_to_image(data->mlx, cub->so_texture, &data->img_w, &data->img_h);
	if (!data->t_ea || !data->t_no || !data->t_so || !data->t_we)
		exit(write(2, "Invalide textur\n", 17));
}

void    parsing(t_cub3d *cub, t_data *data)
{
	int i;

	i = 0;
	while (cub->infile[i])
	{
		if (!(parsing_textur(cub, cub->infile[i])))
			exit(write(2, "Invalide data\n", 15));
		if ((cub->ceilling_rgb) && (cub->ea_texture) && (cub->floor_rgb)
			&& (cub->no_texture) && (cub->so_texture) && (cub->we_texture))
		{	
			ft_init_data(cub, data);
			i++;
			break;
		}
		i++;
	}
	if (!parsing_map(cub, i))
		exit(write(2, "Invalide data\n", 15));
}

int lastlen(char *str)
{
	int i;
	
	i = ft_strlen(str);
	while (str[i] != '1' && i > 0)
		i--;
	return (i);
}

void check_str(char *str)
{
	int i;
	int len;
	int check;

	i = 0;
	len = lastlen(str);
	check = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E'\
			|| str[i] == 'F' ||  str[i] == 'C')
			check++;
		if (check > 6 && str[i] == '1')
		{
			while (i < len)
			{
				if (str[i] == '\n' && str[i + 1] == '\n')
					exit(write(2, "Erorr empty line in map\n", 25));
				i++;
			}
			if (str[i] == '\0')
				break;
		}
		i++;
	}
}

void init_cub(char *file, t_cub3d *cub)
{
	int fd;
	char *str;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(write(2, "error in file or path given\n", 29));
	cub->no_texture = NULL;
	cub->so_texture = NULL;
	cub->we_texture = NULL;
	cub->ea_texture = NULL;
	cub->floor_rgb = NULL;
	cub->ceilling_rgb = NULL;
	cub->p_flag = 0;
	cub->m_flag = 0;
	str = get_next_line(fd);
	check_str(str);
	cub->infile = ft_split(str, '\n');
	close (fd);
}

int main(int ac, char **av)
{
	t_cub3d	cub;
	t_data data;
	int		len;

	if (ac == 2)
	{
		len = ft_strlen(av[1]) - 4;
		if (ft_strncmp(&av[1][len], ".cub", 4))
			exit(write(2, "Invalide file name\n", 20));
		init_cub(av[1], &cub);
		parsing(&cub, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}
