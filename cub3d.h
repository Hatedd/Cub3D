#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include "minilibx_opengl_20191021/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct cub3d
{
    char *no_t;
    char *so_t;
    char *we_t;
    char *ea_t;
    char *floor_rgb;
    char *ceilling_rgb;
    char **infile;
    char **map;
    int  p_flag;
    int  m_flag;
    int  valide;
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
    int  img_h;
    int  img_w;
    int  map_h;
    int  map_w;
}   t_data;



#endif