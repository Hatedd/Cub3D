#ifndef CUB3D_H
# define CUB3D_H

typedef struct cub3d
{
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    char *floor_rgb;
    char *ceilling_rgb;
    char **map;
} t_cub3d;

typedef struct data
{
    void    *mlx;
    void    *win;
}   t_data;



#endif