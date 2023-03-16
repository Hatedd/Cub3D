
#include "../cub3d.h"

void	ft_ray_init(t_data *data)
{
	int i;

	i = 0;
	data->rays = ft_calloc(NUM_RAYS, sizeof(t_rays));
	while(i < NUM_RAYS)
	{
        // data->rays[i].angle = 0;
        data->rays[i].angle = data->player->rotationangle - (FOV / 2);
        data->rays[i].fov = FOV;
        data->rays[i].facing_down = 0;
        data->rays[i].facing_up = 0;
        data->rays[i].facing_right = 0;
        data->rays[i].facing_left = 0;
        data->rays[i].raynum = WIN_WIDHT;
        data->rays[i].washitve = 0;
		i++;
	}
}
int		ft_close_win(void)
{
	exit(0);
	return (0);
}
void drawLine(t_data *d,int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / (float)steps ;
    float yIncrement = dy / (float)steps ;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        int pixelX = (int)x;
        int pixelY = (int)y;
        my_mlx_p_put(d,pixelX, pixelY, color);
        x += xIncrement;
        y += yIncrement;
    }
}





void render_player(t_data *d)
{
    int color = 0xFFFFFF;

    double x0 = d->player->x;
    double y0 = d->player->y;
    // Draw a filled rectangle for the player
//    ft_draw_square(d, color, x0, y0, 10);
    // Draw a line for the direction the player is facing
//    int endX = d->player->x + cos(d->player->rotationangle) * 45;
//     int endY = d->player->y + sin(d->player->rotationangle) * 45;
//     drawLine(d,1.0 *d->player->x, 1.0 *d->player->y,1.0 * endX,1.0 * endY, color);
        // drawLine(d, d->player->x ,d->player->y,d->rays->wallhit_x ,d->rays->wallhit_y, 0xFF0000);
// // int num_rays = sizeof(t_rays) / sizeof(t_rays[0]); // Calculate the number of rays


    

}

int ft_key_press(int key_press, t_data *d)
{
    
  //  printf("beefor%d\n",d->player->walk);
    // printf("key is ----> %d\n ", key_press);
    d->player->flg = 0;
    if (key_press == 13 || key_press == 126 )
    {
        d->player->walk = 1;
   // printf("after%d\n",d->player->walk);
    }
    else if (key_press == 1 || key_press == 125)
        d->player->walk = -1;
    else if (key_press == 0 )
    {
        d->player->flg = 1;
        d->player->walk = -1;
    }
    else if (key_press == 2)
    {
        d->player->flg = 1;
        d->player->walk = 1;
    }
    else if (key_press == 124)
        d->player->turn = 1;
    else if (key_press == 123)
        d->player->turn = -1;   /* code */
    else if (key_press == 53)
        exit(0);
    return (0);
}
int ft_key_relase(int key_press, t_data *d)
{
    // printf("key is ----> %d\n ", key_press);
    if (key_press == 13 || key_press == 126 )
    {
        d->player->walk = 0;
   // printf("after%d\n",d->player->walk);
    }
    else if (key_press == 1 || key_press == 125)
        d->player->walk = 0;
    else if (key_press == 0 )
    {
        d->player->flg = 0;
        d->player->walk = 0;
    }
    else if (key_press == 2)
    {
        d->player->walk = 0;
        d->player->flg = 0;
    }
    else if (key_press == 124)
        d->player->turn =0;
    else if (key_press == 123)
        d->player->turn = 0;   /* code */
    return (0);
}
int is_valid_move(double x, double y) {
    if (x < 0 || x >= WIN_WIDHT || y < 0 || y >= WIN_HIGHT)
     {
        return 0; // new position is outside of game world
    }
    return 1;
}


void    player_init(t_data *d)
{
    d->player->movespeed = 5;
    d->player->turn = 0;
    d->player->walk = 0;
    d->player->flg = 0;

     d->player->rot_speed = 2 * (PI / 180);
     d->player->x = WIN_WIDHT / 2;
    d->player->y = WIN_HIGHT / 2;
      d->player->walk_speed = 5;
    d->player->rotationangle = PI / 2;
}



int mapiswall(t_data *d, int x, int y)
{
	// if (x < d->cub->map_whitd  && y < d->cub->map_hight)
	// {
    //     if(d->cub->map[y][x] && (d->cub->map[y][x] == '1'))
    //         return 1;
    // }
    
    // x = floor(x /TILE);
    // y = floor(y /TILE);
    // printf()
    if (x < 0 || x > d->cub->map_whitd * TILE|| y < 0 || y > 10 * TILE)
		return (1);
    	if ( d->cub->map[y][x] == '1' )
		return (1);
     
        return 0;
   
        
}


void move_player(t_data *d)
{
    
    double movestep ;
    double newx;
    double newy;
    // int pixeltogrid;
    d->player->rotationangle += d->player->turn * d->player->rot_speed ;
    movestep = d->player->walk * d->player->movespeed;
//    printf("after update %d\n",d->player->turn);

    newx = d->player->x + cos (d->player->rotationangle)* movestep;
    newy = d->player->y + sin(d->player->rotationangle ) * movestep;

    // d->player->rotationangle += d->player->rot_speed;

// prevx = d->player->x;
// prevy = d->player->y;
    if (!mapiswall(d, newx / TILE, d->player->y / TILE))
        d->player->x = newx;
    if (!mapiswall(d, d->player->x / TILE, newy / TILE))
        d->player->y = newy;

}
