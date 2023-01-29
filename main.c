#include "cub3d.h"

int parsing(t_cub3d *cub, char *str)
{
    int i;

    i = 0;
    while (check_ws(*str))
        str++;
    if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
}

int check_ws(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int check_empty(char *str)
{
    if (check_ws(*str))
        str++;
    if (*str == '\0')
        return (1);
    return (0);
}

void    parsing(int fd, t_cub3d *cub)
{
    char *str;

    while (str = get_next_line(fd))
    {
        if (!check_empty(str))
        {
            if (!cub_getter(cub, str))
        }
    }
}

int init_cub(char *file, t_cub3d *cub)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        exit(printf("error in file or path given"));
    cub->no_texture = NULL;
    cub->so_texture = NULL;
    cub->we_texture = NULL;
    cub->ea_texture = NULL;
    cub->floor_rgb = NULL;
    cub->ceilling_rgb = NULL;
    return (fd);
}

int main(int ac, char **av)
{
    t_cub3d     cub;
    t_data      data;
    int         fd;

    if (ac > 2)
        printf("Error Invalide args\n");
    fd = init_cub(av[1], &cub);
    parsing(fd, &cub);
    return (0);
}