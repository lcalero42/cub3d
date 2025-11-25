/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:51:16 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/24 17:57:50 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "constants.h"

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_dda_vars
{
	int				map_x;
	int				map_y;
	int				steps;
}					t_dda_vars;

typedef enum e_wall_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}					t_wall_side;

typedef struct s_color
{
	int				base_r;
	int				base_g;
	int				base_b;
	int				fog_r;
	int				fog_g;
	int				fog_b;
}					t_color;

typedef struct s_fog_params
{
	int				x;
	int				wall_start;
	int				wall_end;
	int				fog_alpha;
	int				fog_color;
}					t_fog_params;

typedef struct s_wall_bounds
{
	int				wall_start;
	int				wall_end;
}					t_wall_bounds;

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
	double			perp_wall_dist;
	int				hit;
	int				side;
	int				must_render;
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
	int				is_moving;
}					t_player;

typedef struct s_keys
{
	int				a;
	int				d;
	int				w;
	int				s;
	int				left;
	int				right;
}					t_keys;

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
	char			*addr;
	int				bpp;
	int				line_len;
}					t_texture_info;

typedef struct s_render
{
	void			*texture_img;
	char			*texture_path;
	t_texture_info	info;
	int				texture_endian;
}					t_render;

typedef struct s_mouse
{
	int				first_move;
	int				last_x;
	int				enabled;
	int				sensitivity;
}	t_mouse;

typedef struct s_data
{
	int				game_started;
	t_render		north_wall;
	t_render		south_wall;
	t_render		east_wall;
	t_render		west_wall;
	t_render		crosshair;
	t_color			floor;
	t_color			ceiling;
	void			*render_img;
	t_texture_info	render_info;
	int				render_endian;
	t_sprite		*sprites;
	int				sprite_count;
	int				config_lines;
	void			*mlx;
	void			*window;
	t_player		player;
	t_mouse			mouse;
	t_grid			grid;
	t_ray			rays[WINDOW_WIDTH];
	t_keys			keys;
	int				render_fog;
	int				frame_count;
	double			fps;
	long long		last_time;
}					t_data;

#endif