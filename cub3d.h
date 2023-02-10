#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct cub3d
{
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *floor_rgb;
    char *ceilling_rgb;
    char **infile;
    char **map;
    int  p_flag;
} t_cub3d;

typedef struct data
{
    void    *mlx;
    void    *win;
}   t_data;



#endif