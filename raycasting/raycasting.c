#include "../cub3d.h"

void    my_mlx_p_put(t_data *data, int x, int y, int color)
{
    char    *d;
    if (x < 0 || x >= WIN_WIDHT || y < 0 || y >= WIN_HIGHT)
		return;
    d = data->img->addr + (y * data->img->size + x * (data->img->bit_pp / 8));
    *(unsigned int *) d = color;
}

void draw_border(t_data *d, int i, int j, int color)
{
    int size = 64;
    int x;
    int y;

    x = i*size;
    
    while (x < i*size + size)
    {
        my_mlx_p_put(d, j*size, x,color);
        my_mlx_p_put(d, (j+1)*size-1, x,color) ;
       x++; /* code */
    }
    
    y = j*size; 
    while(y < j*size + size) {
        my_mlx_p_put(d, y, i*size,color);
        my_mlx_p_put(d, y, (i+1)*size-1,color);
        y++;
    }
}

int	ft_strlenn(const	char *s)
{
	int	i;
    if (!s)
        return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int check_next_empty(int i, int j, t_data *d)
{
   if (i == 0 || j == 0 || i == d->cub->map_len - 1 || j == ft_strlenn(d->cub->map[i]) - 1 ||
                    d->cub->map[i-1][j] == '0' || d->cub->map[i][j-1] == '0' ||
                    d->cub->map[i+1][j] == '0' || d->cub->map[i][j+1] == '0')
        return 1;

    return 0;
}

void ft_draw_square(t_data *data, int color, int x, int y, int size)
{
    // Draw the square
    int i = 0;
    int j = 0;

    while (i < TILE)
    {
        j = 0;
        while (j < size)
        {
            my_mlx_p_put(data, x+j, y+i, color);
            j++;
        }
        i++;
    }
}

void ft_render3d(t_data *data, int ray_index)
{
	int wall_strip_height;
	int wall_bottom_pixel;
	int wall_top_pixel;
	double perpendicular_hit_distance;
	double distance_projection_plane;
	double projected_wall_height;
	int pixel_index_y;
    int distanceFtop;
    int textureOffsetx;
    int textureOffsety;

	// Calculate the perpendicular distance from the player's position to the wall hit by the ray
	perpendicular_hit_distance = data->rays[ray_index].hit_dist * cos(data->rays[ray_index].angle - data->player->rotationangle);

	// Calculate the distance from the player to the projection plane
	distance_projection_plane = (WIN_WIDHT / 2) / tan(data->rays->fov / 2);

	// Calculate the projected height of the wall on the projection plane
	projected_wall_height = (TILE / perpendicular_hit_distance) * distance_projection_plane;

	// Calculate the integer height of the wall on the screen
	wall_strip_height = (int)projected_wall_height;

	// Calculate the top and bottom pixel indices of the wall on the screen
	wall_top_pixel = (WIN_HIGHT / 2) - (wall_strip_height / 2);
	wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
	wall_bottom_pixel = (WIN_HIGHT / 2) + (wall_strip_height / 2);
	wall_bottom_pixel = wall_bottom_pixel > WIN_HIGHT ? WIN_HIGHT : wall_bottom_pixel;

	// Loop through the pixels on the screen that correspond to the wall and draw them
	pixel_index_y = wall_top_pixel;
    if (data->rays[ray_index].hit_vertical)
        textureOffsetx = (int)data->rays[ray_index].wallhit_y % TILE;
    else
        textureOffsetx = (int)data->rays[ray_index].wallhit_x % TILE;
	while(pixel_index_y < wall_bottom_pixel)
	{
        distanceFtop = pixel_index_y + (wall_strip_height / 2) - (WIN_HIGHT / 2);
        textureOffsety = distanceFtop * ((float)TILE/wall_strip_height);
		my_mlx_p_put(data, ray_index, pixel_index_y, *(int*)(data->address + textureOffsety)); // Draw a blue pixel at the current (ray, pixel) position
		pixel_index_y++;
	}
    // int size = 512;
    // for (size_t i = 0; i < size; i++)
	// {
	// 	for (size_t j = 0; j < size; j++)
	// 	{
    //         // unsigned int offset = (int)(i/(((float)size/TILE))) * TILE * 4 + (int)(j/(((float)size/TILE))) * 4;
    //         // unsigned int color = *(unsigned int*)(data->address + offset);
	// 		my_mlx_p_put(data, j, i, color);
	// 	}
	// }
}

void render_map(t_data *data)
{
    int i = 0, j = 0;
    int size = 64;

    while (i < data->cub->map_len)
    {
        j = 0;
        while (j < ft_strlenn(data->cub->map[i]))
        {
            if (data->cub->map[i][j] == '1')
            {
                if (check_next_empty(i, j, data) == 1)
                    draw_border(data, i, j,0x0000F0);
                else
                    ft_draw_square(data, 0xFFFF00, j * size, i * size, size);
            }else if (data->cub->map[i][j] == '0')
            {
                 ft_draw_square(data, 0x00FF00, j * size, i * size, size);
                  draw_border(data, i, j, 0x0000F0); // Green square for example
            }
            j++;
        }
        i++;
   
	}
    }





void normalize_radians(double angle)
{
    angle = fmod(angle  ,(2 * PI));
    if (angle < 0)
    {
        angle += (2 * PI);
    } 
}
// int facing_down(double angle)
// {
//     if (angle > 0 && angle < PI)
//         return 1;
//     return 0;
// }

// int facing_right(double angle)
// {
//     if (angle > 1.5 * PI || angle < 0.5 * PI)
//         return 1;
//     return 0;

// }
// int is_whithing_bound(t_data *d)
// {
//     if ( d->rays->nextx_contact >= 0 && d->rays->nextx_contact <= d->cub->map_whitd * TILE&&
//             d->rays->nexty_contact >=0 && d->rays->nexty_contact <= d->cub->map_hight * TILE)
//             return 1;
//     return 0 ;
// }

int	ft_map_width(char **s)
{
	int l;
	int index;

	index = 0;
	l = 0;
	while(s[index])
	{
		if((size_t)l < ft_strlen(s[index]))
			l = ft_strlen(s[index]);
		index++;
	}
	return (l);
}
int	ft_map_hight(char **s)
{
	int index;

	index = 0;
	while(s[index])
		index++;
	return (index);
}

int mapHasWallAt(double x, double y, t_data *d)
{
    int mapGridIndexX = floor(x);
    int mapGridIndexY = floor(y);

          if (x < 0 || x > TILE * d->cub->map_whitd|| y < 0 || y > d->cub->map_hight * TILE)
        return 1;
    if (mapGridIndexX < 0 || mapGridIndexX >= d->cub->map_whitd || mapGridIndexY < 0 || mapGridIndexY >= d->cub->map_hight) {
        return 1;
    }

    return d->cub->map[mapGridIndexY][mapGridIndexX] == '1';
}

double resize_radians(double angle) {
    angle = fmod(angle, (2.0 *PI));
    if (angle < 0) {
        angle =( 2 * PI )+ angle;
    }
    return angle;
}

double hit_dis_bp(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
double dbp(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
int  get_wall_cordinates(double x, double y, t_data *d) 
{
        if (x < 0 || x > WIN_WIDHT || y < 0 || y > WIN_HIGHT) {
            return 0;
        }
        int mapGridIndexX = floor(x / TILE);
        int mapGridIndexY = floor(y / TILE);
        return d->cub->map[mapGridIndexY][mapGridIndexX] -48;
    }
void find_h_wall(t_cast_ray *casting, t_data *d)
{

        // Increment deltax and deltay until we find a wall
        while (casting->next_x_intersect >= 0 && casting->next_x_intersect <= WIN_WIDHT && casting->next_y_intersect >= 0 && casting->next_y_intersect <= WIN_HIGHT) {
            double wallcontent = get_wall_cordinates(
                casting->next_x_intersect,
                casting->next_y_intersect + (casting->up ? -1 : 0) // if ray is facing up, force one pixel up so we are inside a grid cell
            ,d);
            if (wallcontent != 0) {
            casting->found_h_wall = 1;
            casting->horzhit_x = casting->next_x_intersect;
            casting->horzhit_y = casting->next_y_intersect;
                break;
            } else {
                casting->next_x_intersect += casting->deltax;
                casting->next_y_intersect += casting->deltay;
            }
        }
}
void find_h_dist(t_data *d, double ray_angle, int i, t_cast_ray *casting)
{
    
        ///////////////////////////////////////////
        // HORIZONTAL RAY-GRID INTERSECTION CODE
        ///////////////////////////////////////////
        casting->found_h_wall = 0;
        casting->horzhit_x = 0;
        casting->horzhit_y = 0;

        d->rays[i].angle = ray_angle;

        // Find the y-coordinate of the closest horizontal grid intersenction
        casting->y_intersect = floor(d->player->y / TILE) * TILE;
        casting->y_intersect +=  casting->down ? TILE : 0;

        // Find the x-coordinate of the closest horizontal grid intersection
        casting->x_intersect = d->player->x + (casting->y_intersect - d->player->y) / tan(ray_angle);

        // Calculate the increment deltax and deltay
        casting->deltay = TILE;
        casting->deltay *= casting->up ? -1 : 1;

        casting->deltax = TILE / tan(ray_angle);
        casting->deltax *= (casting->left && casting->deltax > 0) ? -1 : 1;
        casting->deltax *= (casting->right && casting->deltax < 0) ? -1 : 1;

        casting->next_x_intersect = casting->x_intersect;
        casting->next_y_intersect = casting->y_intersect;

        find_h_wall(casting, d);
   
}

void find_v_wall(t_cast_ray *casting, t_data *d)
{

        while (casting->nextVertTouchX >= 0 && casting->nextVertTouchX <= WIN_WIDHT&& casting->nextVertTouchY >= 0 && casting->nextVertTouchY <= WIN_HIGHT) {
            int wallcontent = get_wall_cordinates(
                casting->nextVertTouchX + (casting->left? -1 : 0), // if ray is facing left, force one pixel left so we are inside a grid cell
                casting->nextVertTouchY
            ,d);
            // printf(" wall content%d\n", wallcontent);
            if (wallcontent != 0) {
                casting->found_v_wall = 1;
                casting->verthit_x = casting->nextVertTouchX;
                casting->verthit_y = casting->nextVertTouchY;
                break;
            } else {
                // printf(" not wall\n");
                casting->nextVertTouchX += casting->deltax;
                casting->nextVertTouchY += casting->deltay;
            }
        }
}

void find_v_dist(t_data *d, double ray_angle, int i, t_cast_ray *casting)
{
        ///////////////////////////////////////////
        // VERTICAL RAY-GRID INTERSECTION CODE
        ///////////////////////////////////////////
        casting->found_v_wall = 0;
        casting->verthit_x = 0;
        casting->verthit_y = 0;

        // Find the x-coordinate of the closest vertical grid intersenction
        casting->x_intersect = floor(d->player->x / TILE) * TILE;
        casting->x_intersect += casting->right? TILE : 0;

        // Find the y-coordinate of the closest vertical grid intersection
        casting->y_intersect = d->player->y + (casting->x_intersect - d->player->x) * tan(ray_angle);

        // Calculate the increment deltax and deltay
        casting->deltax = TILE;
        casting->deltax *= casting->left ? -1 : 1;

        casting->deltay = TILE * tan(ray_angle);
        casting->deltay *= (casting->up && casting->deltay > 0) ? -1 : 1;
        casting->deltay *= (casting->down && casting->deltay < 0) ? -1 : 1;

        casting->nextVertTouchX = casting->x_intersect;
        casting->nextVertTouchY = casting->y_intersect;

        // Increment deltax and deltay until we find a wall
        find_v_wall(casting, d);
}
void save_smallest_distance(t_cast_ray *casting, int i, t_data *d)
{
        // Calculate both horizontal and vertical hit_dists and choose the smallest value
        casting->hit_dis_h = (casting->found_h_wall)
            ? hit_dis_bp(d->player->x, d->player->y, casting->horzhit_x, casting->horzhit_y)
            :INT_MAX;
        casting->hit_dis_ver = (casting->found_v_wall)
            ? hit_dis_bp(d->player->x, d->player->y, casting->verthit_x, casting->verthit_y)
            : INT_MAX;

        // only store the smallest hit_dist
        if (casting->hit_dis_ver < casting->hit_dis_h) {
            casting->hit_x = casting->verthit_x;
            casting->hit_y = casting->verthit_y;
            casting->hit_dist = casting->hit_dis_ver;
            casting->is_hitvertical = 1;
        } else {
            casting->hit_x = casting->horzhit_x;
            casting->hit_y = casting->horzhit_y;
            casting->hit_dist = casting->hit_dis_h;
            casting->is_hitvertical = 0;
        }
    d->rays[i].hit_dist = casting->hit_dist;
}

void castRay( t_data *d , double ray_angle , int i)
{
    t_cast_ray casting;

         casting.down = ray_angle > 0 && ray_angle < PI;
         casting.up = !casting.down;
         casting.right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
         casting.left = !casting.right;
        casting.hit_x = 0;
        casting.hit_y = 0;
        casting.hit_dist = 0;
        casting.is_hitvertical = 0;

       find_h_dist(d, ray_angle, i,&casting);
      find_v_dist(d, ray_angle, i, &casting);
    save_smallest_distance(&casting, i,d);
}

void ft_castrays(t_data *d) {

    t_cast_ray   casting;  
 double ray_angle = d->player->rotationangle - (FOV / 2);
    for (int i = 0; i < NUM_RAYS ; i++) {
     ray_angle = resize_radians(ray_angle);
     d->rays[i].angle = ray_angle;
        castRay(d,ray_angle, i);
        ray_angle += FOV / NUM_RAYS;
	    ft_render3d(d, i);
    }
}
int raycasting(t_data *d)
{
    int i;

    if (!d->img->img)
    {
        d->img->img =  mlx_new_image(d->mlx, WIN_WIDHT, WIN_HIGHT);           
        d->img->addr = mlx_get_data_addr(d->img->img, &d->img->bit_pp, &d->img->size, &d->img->end);
    }
    if (d->flag == 1)
        mlx_clear_window(d->mlx,d->win);

    move_player(d);
    render_floor_roof(d);
    ft_castrays(d);
    // render_map(d);
    // render_player(d);
    mlx_put_image_to_window(d->mlx, d->win, d->img->img, 0,0 );
    mlx_destroy_image(d->mlx, d->img->img);
    d->img->img = 0;
    d->flag = 1;

    return 0;
}