#include "cub3d.h"

void    ft_free(char **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

int ft_check_rgb(char *rgb)
{
    int i;
    int len;
    char **tmp;

    len = ft_strlen(rgb);
    tmp = ft_split(rgb + 2, ',');
    if (rgb[len - 1] == ',')
        exit(printf("don't do that here :("));
    i = 0;
    while (tmp[i] != NULL)
    {
        len = ft_atoi(tmp[i]);
        if (len > 255)
            return (0);
        i++;
    }
    return (0);
}

int check_ws(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int ft_floor_ceilling(t_cub3d *cub, char *str)
{
    int i;
    int j;

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
    if (ft_strncmp(str, "C", 1) == 0)
        cub->ceilling_rgb = ft_substr(str, i, j);
    if (cub->floor_rgb)
        return (ft_check_rgb(cub->floor_rgb));
    else if (cub->ceilling_rgb)
        return (ft_check_rgb(cub->ceilling_rgb));
}

int ft_texture(t_cub3d *cub, char *str)
{
    int i;
    int j;

    if ((ft_strncmp(str, "NO", 2) == 0 && cub->no_texture)
        || (ft_strncmp(str, "SO", 2) == 0 && cub->so_texture)
        || (ft_strncmp(str, "WE", 2) == 0 && cub->we_texture)
        || (ft_strncmp(str, "EA", 2) == 0 && cub->ea_texture))
        return (0);
    i = 2;
    while (check_ws(*str + i))
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

int parsing(t_cub3d *cub, char *str)
{
    int i;

    i = 0;
    while (check_ws(*str))
        str++;
    if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
        i = ft_texture(cub, str);
    else if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
        i = ft_floor_ceilling(cub, str);
    return (i);
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
                exit(printf("Invalide data\n"));
            if ((cub->ceilling_rgb) && (cub->ea_texture) && (cub->floor_rgb)
                && (cub->no_texture) && (cub->so_texture) && (cub->we_texture))
                break;
        }
        ft_free(&str);
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