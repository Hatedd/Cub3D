#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
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
    int  m_flag;
    int  map_len;
}   t_cub3d;

typedef struct data
{
    void    *mlx;
    void    *win;
    void    *t_no;
    void    *t_so;
    void    *t_we;
    void    *t_ea;
}   t_data;



#endif