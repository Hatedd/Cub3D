/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:37:39 by yobenali          #+#    #+#             */
/*   Updated: 2023/03/17 05:20:01 by yobenali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <stddef.h>
# define PI 3.141592653589793
# define WIN_WIDHT 1280
# define WIN_HIGHT 640
# define TILE 64
# define T TILE
# define FOV (60 * (PI / 180))
# define EDGINGWIDTH 30
# define NUM_RAYS WIN_WIDHT
# define SCALE_FACTOR 4 // or any other value you want
# define TWO_PI 6.28318530
# define INT_MAX 2147483647

typedef struct s_img
{
	void	*img;
	int		bit_pp;
	int		end;
	int		size;
	char	*addr;
}	t_img;

typedef struct cub3d
{
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	char	*floor_rgb;
	char	*ceilling_rgb;
	char	**infile;
	char	**map;
	char	*textures;
	int		map_whitd;
	int		map_hight;
	int		p_flag;
	int		m_flag;
	int		valide;
	int		map_len;
	int		num_rows;
	int		num_cols ;
}	t_cub3d;

typedef struct s_player
{
	double	x;
	double	y;
	double	w;
	double	h;
	double	rotationangle;
	double	rot_speed;
	double	walk_speed;
	double	movespeed;
	int		turn;
	int		walk;
	int		flg;
}	t_player;

typedef struct s_rays
{
	int		hit_vertical;
	int		facing_left;
	int		facing_right;
	int		facing_up;
	int		facing_down;
	int		washitve;
	int		raynum;
	double	wallhit_x;
	double	wallhit_y;
	double	wallhit_vx;
	double	wallhit_vy;
	double	hit_dist;
	double	intersection_horiz;
	double	intersection_verti;
	double	x_contact_point;
	double	y_contact_point;
	double	nextx_contact;
	double	nexty_contact;
	double	nextvx_contact;
	double	nextvy_contact;
	double	delta_x;
	double	delta_y;
	double	cast_angle;
	double	fov;
	double	angle;
}t_rays;

typedef struct s_castray
{
	double	v_dist;
	double	h_dist;
	double	x_intersect;
	double	y_intersect;
	double	deltax;
	double	deltay;
	double	next_x_intersect;
	double	next_y_intersect;
	double	nextVertTouchX;
	double	nextVertTouchY;
	double	hit_dis_h;
	double	hit_dis_ver;
	double	hit_dist;
	double	hit_x ;
	double	hit_y ;
	double	is_hitvertical;
	double	found_h_wall;
	double	horzhit_x ;
	double	horzhit_y ;
	double	found_v_wall;
	double	verthit_x ;
	double	verthit_y ;
	int		down;
	int		up ;
	int		right;
	int		left;
}t_cast_ray;

typedef struct data
{
	void		*mlx;
	void		*win;
	void		*t_no;
	void		*t_so;
	void		*t_we;
	void		*t_ea;
	char		*address;
	int			row;
	int			col;
	int			floor_color;
	int			ceiling_color;
	int			flag;
	int			img_h;
	int			img_w;
	int			map_h;
	int			map_w;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_player	*player;
	t_cub3d		*cub;
	t_rays		*rays;
	t_img		*img;
}	t_data;

int		check_ws(char c);
int		ft_close_win(void);
int		raycasting(t_data *d);
int		ft_map_width(char **s);
int		ft_map_hight(char **s);
int		ft_strlenn(const char *s);
int		mat_len(t_cub3d *cub, int pos);
int		ft_key_press(int key, t_data *d);
int		ft_texture(t_cub3d *cub, char *str);
int		ft_key_relase(int key_press, t_data *d);
int		ft_floor_ceilling(t_cub3d *cub, char *str);
int		mapHasWallAt(double x, double y, t_data *d);
int		get_wall_cordinates(double x, double y, t_data *d);

void	ft_freee(char **ptr);
void	ft_updown(char *str);
void	ft_midline(char *str);
void	parsing(t_cub3d *cub);
void	img_init(t_data *data);
void	player_init(t_data *d);
void	move_player(t_data *d);
void	ft_castrays(t_data *d);
void	render_player(t_data *d);
void	ft_chflood(t_cub3d *cub);
void	render_map(t_data *data);
void	img_assigne(t_data *data);
void	ft_ray_init(t_data *data);
void	my_get_data_addr(t_data *data);
void	render_floor_roof(t_data *data);
void	init_cub(char *file, t_cub3d *cub);
void	creat_win(t_data *data, t_img *img);
void	cast_ray(t_data *d, double ray_angle, int i);
void	ft_init_data(t_cub3d *cub, t_data *d, t_img *img);
void	my_mlx_p_put(t_data *data, int x, int y, int color);
void	ft_walls_check(t_cub3d *cub, int i, int j, int flag);
void	get_array_dimensions(t_cub3d *cub, int *rows, int *cols);
void	save_smallest_distance(t_cast_ray *casting, int i, t_data *d);
void	drawLine(t_data *d, int x1, int y1, int x2, int y2, int color);
void	ft_draw_square(t_data *data, int color, int x, int y, int size);


#endif
