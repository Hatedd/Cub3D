#include "cub3d.h"

int init_cub(char *file, t_cub3d *cub)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        printf("error in file or path given");
    cub->no_texture = NULL;
    cub->so_texture = NULL;
    cub->we_texture = NULL;
    cub->ea_texture = NULL;
    cub->floor_rgb = NULL;
    cub->ceilling_rgb = NULL;
}

int main(int ac, char **av)
{
    t_cub3d     cub;
    t_data      data;
    int         fd;

    if (ac > 2)
        printf("Error Invalide args\n");
    fd = init_cub(av[1], &cub);
    return (0);
}