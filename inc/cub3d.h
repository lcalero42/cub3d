/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:01:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/17 22:08:11 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 640
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 480
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 0.1
# endif

# ifndef ROTATION_SPEED
#  define ROTATION_SPEED 0.05
# endif

# define FOV 1.047198f

typedef enum e_wall_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}					t_wall_side;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_ray
{
	t_vector		ray_dir;
	t_vector		map_pos;
	t_vector		side_dist;
	t_vector		delta_dist;
	t_vector		step;
	int				hit;
	int				side;
}					t_ray;

typedef struct s_grid
{
	char			**grid;
	int				width;
	int				height;
}					t_grid;

typedef struct s_player
{
	t_vector		position;
	t_vector		camera_segment;
	t_vector		dir;
	double			fov;
	double			angle;
}					t_player;

typedef struct s_sprite
{
	double			x;
	double			y;
	int				texture_id;
	double			distance;
}					t_sprite;

typedef struct s_sprite_calc
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
}					t_sprite_calc;

typedef struct s_texture_info
{
	char	*addr;
	int		bpp;
	int		line_len;
}	t_texture_info;

typedef struct s_wall_render
{
	void			*wall_texture_img;
	t_texture_info	info;
	int				wall_texture_endian;
}					t_wall_render;

typedef struct s_data
{
	t_wall_render	north_wall;
	t_wall_render	south_wall;
	t_wall_render	east_wall;
	t_wall_render	west_wall;
	void			*render_img;
	char			*render_addr;
	int				render_bpp;
	int				render_line_len;
	int				render_endian;
	t_sprite		*sprites;
	int				sprite_count;
	void			*mlx;
	void			*window;
	t_player		player;
	t_grid			grid;
	t_ray			rays[WINDOW_WIDTH];
}					t_data;

// FUNCTIONS
void				trace_ray(t_data *data, double angle);
void				render_walls(t_data *data);
void				init_walls(t_data *data);
void				clear_screen(t_data *data);
void				put_pixel_to_image(t_data *data, int x, int y, int color);
int					get_wall_texture_pixel(t_data *data, int x, int y,
						int side);
int					determine_movement(int keycode, t_data *data);
t_wall_side			get_wall_side(t_data *data, int ray_index);
t_texture_info		get_texture_info_by_side(t_data *data, t_wall_side side);

// RAYCASTING INIT FUNCTIONS
void				init_player_direction(t_data *data, double angle);
void				init_ray_direction(t_data *data, int i);
void				init_ray_distances(t_data *data, int i);
void				init_ray_steps(t_data *data, int i);

#endif