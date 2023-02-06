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

    len = 2;
    while (rgb[len])
    {
        i = 0;
        while (ft_isdigit(rgb[len]) && rgb[len])
            len++;
        while (!ft_isdigit(rgb[len])  && rgb[len] )
        {
            len++;
            i++;
        }
        if (i > 1)
            exit(write(2, "Invalide rgb data\n", 19));
    }
    tmp = ft_split(rgb + 2, ',');
    i = 0;
    while (tmp[i] != NULL)
    {
        len = ft_atoi(tmp[i]);
        if (len > 255)
            return (0);
        i++;
    }
    return (1);
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
    return (1); 
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

int parsing_textur(t_cub3d *cub, char *str)
{
    int i;

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
}

int mat_len(t_cub3d *cub)
{
    int i;

    i = 0;
    while (cub->map[i])
        i++;
    return (i);
}

int     parsing_map(t_cub3d *cub, int pos)
{
    int i;
    int j;
    int len;

    i = 0;
    len = mat_len(cub);
    cub->map = malloc(sizeof(char *) * len);
    ft_copy_map(cub, pos);
    while (cub->map[i])
    {
        j = 0;
        while (check_ws(cub->map[i][j]))
        {
            j++;
            if ((i == 0 || i = len -1))
        }
        {
            printf("%d\n", j);
            exit(write(2, "Invalide map :(\n", 17));
        }
        if (i == len - 1 && !check_ws(cub->map[i][j]) && cub->map[i][j] != 1 \
            && cub->map[i][j])
            exit(write(2, "Invalide map :(\n", 17));
        i++;
    }
    return (0);
}

void    parsing(t_cub3d *cub)
{
    int i;

    i = 0;
    while (cub->infile[i])
    {
        if (!parsing_textur(cub, cub->infile[i]))
        {
            if (!parsing_map(cub, i))
                exit(printf("Invalide data\n"));
        }
        i++;
    }
    if ((cub->ceilling_rgb) && (cub->ea_texture) && (cub->floor_rgb)
        && (cub->no_texture) && (cub->so_texture) && (cub->we_texture))
    {
        return ;
    }
    else
        exit(write(2, "Error missing data\n", 20));
}
void init_cub(char *file, t_cub3d *cub)
{
    int fd;

    char *str;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        exit(printf("error in file or path given"));
    cub->no_texture = NULL;
    cub->so_texture = NULL;
    cub->we_texture = NULL;
    cub->ea_texture = NULL;
    cub->floor_rgb = NULL;
    cub->ceilling_rgb = NULL;
    str = get_next_line(fd);
    cub->infile = ft_split(str, '\n');
    int i = 0;
    while(cub->infile[i])
    {
        printf("%s\n", cub->infile[i]);
        i++;
    }
    close (fd);
}

int main(int ac, char **av)
{
    t_cub3d     cub;
    // t_data      data;
    int         len;
    
    if (ac > 2)
        printf("Error Invalide args\n");
    len = ft_strlen(av[1]) - 4;
    if (ft_strncmp(&av[1][len], ".cub", 4))
        exit(write(2, "Invalide file name\n", 20));
    init_cub(av[1], &cub);
    parsing(&cub);
    // system("leaks Cub3D");
    return (0);
}