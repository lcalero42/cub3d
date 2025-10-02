/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:18:32 by lcalero           #+#    #+#             */
/*   Updated: 2025/10/02 15:59:18 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_BONUS_H
# define STRUCTURES_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "constants_bonus.h"

typedef enum e_wall_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}	t_wall_side;

typedef struct s_health_bar
{
	int	current_health;
	int	max_health;
	int	x;
	int	y;
	int	width;
	int	height;
}	t_health_bar;

typedef struct s_enemy_health_bar
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_enemy_health_bar;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_dda_vars
{
	int	map_x;
	int	map_y;
	int	steps;
}	t_dda_vars;

typedef struct s_color
{
	int	base_r;
	int	base_g;
	int	base_b;
	int	fog_r;
	int	fog_g;
	int	fog_b;
}	t_color;

typedef struct s_fog_params
{
	int	x;
	int	wall_start;
	int	wall_end;
	int	fog_alpha;
	int	fog_color;
}	t_fog_params;

typedef struct s_wall_bounds
{
	int	wall_start;
	int	wall_end;
}	t_wall_bounds;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	ray_dir;
	t_vector	map_pos;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_vector	step;
	double		perp_wall_dist;
	int			hit;
	int			side;
	int			must_render;
}	t_ray;

typedef struct s_grid
{
	char	**grid;
	int		width;
	int		height;
}	t_grid;

typedef struct s_player
{
	t_vector	position;
	t_vector	camera_segment;
	t_vector	dir;
	double		fov;
	double		pitch_offset;
	double		angle;
	int			is_moving;
	double		pitch;
	double		stamina;
	int			is_running;
	double		current_health;
	double		max_health;
}	t_player;

typedef struct s_keys
{
	int	a;
	int	d;
	int	w;
	int	s;
	int	left;
	int	right;
	int	run;
}	t_keys;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texture_id;
	double	distance;
}	t_sprite;

typedef struct s_sprite_calc
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_calc;

typedef struct s_texture_info
{
	char	*addr;
	int		bpp;
	int		line_len;
}	t_texture_info;

typedef struct s_render
{
	void			*texture_img;
	char			*texture_path;
	t_texture_info	info;
	int				texture_endian;
}	t_render;

typedef struct s_anim
{
	t_render		render_arr[MAX_ANIM_LENGTH];
	int				is_playing;
	unsigned int	index;
}	t_anim;

typedef struct s_sprite_bounds
{
	int	start_x;
	int	end_x;
	int	half_width;
	int	sprite_height;
	int	sprite_top;
}	t_sprite_bounds;

typedef struct s_sprite_params
{
	t_texture_info	*tex_info;
	int				x;
	int				tex_x;
	int				sprite_top;
	int				sprite_height;
}	t_sprite_params;

typedef struct s_enemy_render_data
{
	int		visible;
	int		screen_x;
	int		sprite_height;
	int		sprite_top;
	double	angle_diff;
}	t_enemy_render_data;

typedef struct s_mouse
{
	int		first_move;
	int		last_x;
	int		last_y;
	int		delta_x;
	int		delta_y;
	int		center_x;
	int		center_y;
	int		enabled;
	double	sensitivity;
}	t_mouse;

typedef struct s_enemy
{
	t_vector			position;
	t_render			render;
	t_enemy_render_data	enemy_data;
	int					current_health;
	int					max_health;
}	t_enemy;

typedef struct s_astar_node
{
	t_pos				pos;
	int					g_cost;
	int					h_cost;
	int					f_cost;
	struct s_astar_node	*parent;
	int					open;
	int					closed;
}	t_astar_node;

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	dx;
	double	dy;
	double	ray_dx;
	double	ray_dy;
	double	discriminant;
}	t_discriminant;

typedef struct s_astar_data
{
	t_astar_node	nodes[MAX_NODES];
	int				node_count;
	int				width;
	int				height;
}	t_astar_data;

typedef struct s_movement_data
{
	double	move_speed;
	t_pos	start;
	t_pos	goal;
	t_pos	path[128];
}	t_movement_data;

typedef struct s_data
{
	int				game_started;
	t_render		north_wall;
	t_render		south_wall;
	t_render		east_wall;
	t_render		west_wall;
	t_render		enemy_render;
	t_render		crosshair;
	t_render		door;
	t_anim			gun;
	t_anim			shot;
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
	t_enemy			enemy;
	t_mouse			mouse;
	t_grid			grid;
	t_ray			rays[WINDOW_WIDTH];
	t_ray			shot_ray;
	t_keys			keys;
	int				render_fog;
	int				frame_count;
	double			fps;
	long long		last_time;
	long long		last_shot_time;
	t_discriminant	disc;
	t_health_bar	health_bar;
	t_health_bar	stamina_bar;
}	t_data;

typedef struct s_neighbor_context
{
	t_data			*data;
	t_astar_data	*astar;
	t_pos			goal;
	int				(*visited)[400];
}	t_neighbor_context;

#endif