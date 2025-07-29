/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:01:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/29 12:34:42 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 640
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 480
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 3.0f
# endif

# ifndef ROTATION_SPEED
#  define ROTATION_SPEED 3.0f
# endif

# ifndef RENDER_DISTANCE
#  define RENDER_DISTANCE 1000
# endif

# define FOG_START_DISTANCE 0.1f
# define FOG_END_DISTANCE 8.0f
# define FOG_MAX_ALPHA 255
# define FOG_COLOR_R 0
# define FOG_COLOR_G 0
# define FOG_COLOR_B 0

# define FOV 60.0f
# define CAMERA_PLANE_LENGTH 0.57735f

# define RAY_HIT 1
# define RAY_CONTINUE 0

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

typedef struct s_wall_render
{
	void			*wall_texture_img;
	char			*texture_path;
	t_texture_info	info;
	int				wall_texture_endian;
}					t_wall_render;

typedef struct s_data
{
	t_wall_render	north_wall;
	t_wall_render	south_wall;
	t_wall_render	east_wall;
	t_wall_render	west_wall;
	t_color			floor;
	t_color			ceiling;
	void			*render_img;
	char			*render_addr;
	int				render_bpp;
	int				render_line_len;
	int				render_endian;
	t_sprite		*sprites;
	int				sprite_count;
	int				config_lines;
	void			*mlx;
	void			*window;
	t_player		player;
	t_grid			grid;
	t_ray			rays[WINDOW_WIDTH];
	t_keys			keys;
	int				render_fog;
	int				frame_count;
	double			fps;
	long long		last_time;
}					t_data;

// PARSING
int					parse_file(char *filename, t_data *data);
int					parse_map(char **all_lines, t_data *data);
int					parse_config_section(char **all_lines, t_data *data);
int					parse_texture_path(char **texture_ptr, char *path);
int					parse_color(char *color_str, t_color *color);
int					check_file_extension(char *filename);
int					validate_config(t_data *data);
int					find_player_pos(t_data *data);

// CHECKER
int 				check_map(t_data *data);
int					is_map_surrounded(char **map, int height, int width);

// FUNCTIONS
// RAYCASTING/RENDERING FUNCTIONS
void				trace_ray(t_data *data, double angle);
void				render_walls(t_data *data);
void				init_walls(t_data *data);
void				clear_screen(t_data *data);
void				put_pixel_to_image(t_data *data, int x, int y, int color);
int					get_wall_texture_pixel(t_data *data, int x, int y,
						int side);
void				update_player_movement(t_data *data);
t_wall_side			get_wall_side(t_data *data, int ray_index);
t_texture_info		get_texture_info_by_side(t_data *data, t_wall_side side);
void				apply_fog_overlay(t_data *data);

// RAYCASTING INIT FUNCTIONS
void				init_player_direction(t_data *data, double angle);
void				init_ray_direction(t_data *data, int i);
void				init_ray_distances(t_data *data, int i);
void				init_ray_steps(t_data *data, int i);

// UTILS
int					u_rgb_to_hex(int r, int g, int b, int a);
int					u_is_empty_line(char *line);
int					u_is_config_line(char *line);
void				u_calculate_map_width(t_data *data);
void				u_ft_free(char **res);
int					close_window(t_data *data);
void				u_print_error(char *msg);
int					u_is_empty_line(char *line);
int					u_is_config_line(char *line);
void				u_calculate_map_width(t_data *data);
void				u_ft_free(char **res);
long long			get_current_time(void);
void				calculate_fps(t_data *data);
void				extract_base_colors(int base_color, int *r, int *g, int *b);
void				extract_fog_colors(int fog_color, int *r, int *g, int *b);
int					calculate_fog_alpha(double distance);
int					get_pixel_from_image(t_data *data, int x, int y);
int					blend_colors(t_color *colors, double alpha);

#endif