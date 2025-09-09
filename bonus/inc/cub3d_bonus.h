/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:01:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/09 20:29:47 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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
#  define MOVE_SPEED 7.0f
# endif

# define ENEMY_SPEED 2.0f

# ifndef SENSITIVITY
#  define SENSITIVITY 100
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

# ifndef CROSSHAIR_SIZE
#  define CROSSHAIR_SIZE 10
# endif

# ifndef CROSSHAIR_THICKNESS
#  define CROSSHAIR_THICKNESS 2
# endif

# ifndef CROSSHAIR_COLOR
#  define CROSSHAIR_COLOR 0x00FF00
# endif

# define MAX_GRID_HEIGHT 400
# define MAX_GRID_WIDTH 400
# define MAX_NODES 4096

# ifndef PITCH_MAX
#  define PITCH_MAX 3.0f
# endif

# ifndef PITCH_MIN
#  define PITCH_MIN -3.0f
# endif

# ifndef STAMINA_DRAIN_RATE
#  define STAMINA_DRAIN_RATE 20.0f
# endif

# ifndef STAMINA_REGEN_RATE
#  define STAMINA_REGEN_RATE 10.0f
# endif

# ifndef MAX_STAMINA
#  define MAX_STAMINA 15.0f
# endif

# ifndef RUN_MULTIPLIER
#  define RUN_MULTIPLIER 1.6f
# endif

# define ANIMATION_INTERVAL 2

# define MAX_ANIM_LENGTH 4

typedef struct s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct s_dda_vars
{
	int					map_x;
	int					map_y;
	int					steps;
}						t_dda_vars;

typedef enum e_wall_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}						t_wall_side;

typedef struct s_color
{
	int					base_r;
	int					base_g;
	int					base_b;
	int					fog_r;
	int					fog_g;
	int					fog_b;
}						t_color;

typedef struct s_fog_params
{
	int					x;
	int					wall_start;
	int					wall_end;
	int					fog_alpha;
	int					fog_color;
}						t_fog_params;

typedef struct s_wall_bounds
{
	int					wall_start;
	int					wall_end;
}						t_wall_bounds;

typedef struct s_vector
{
	double				x;
	double				y;
}						t_vector;

typedef struct s_ray
{
	t_vector			ray_dir;
	t_vector			map_pos;
	t_vector			side_dist;
	t_vector			delta_dist;
	t_vector			step;
	double				perp_wall_dist;
	int					hit;
	int					side;
	int					must_render;
}						t_ray;

typedef struct s_grid
{
	char				**grid;
	int					width;
	int					height;
}						t_grid;

typedef struct s_player
{
	t_vector			position;
	t_vector			camera_segment;
	t_vector			dir;
	double				fov;
	double				pitch_offset;
	double				angle;
	int					is_moving;
	double				pitch;
	double				stamina;
	int					is_running;
}						t_player;

typedef struct s_keys
{
	int					a;
	int					d;
	int					w;
	int					s;
	int					left;
	int					right;
	int					run;
}						t_keys;

typedef struct s_sprite
{
	double				x;
	double				y;
	int					texture_id;
	double				distance;
}						t_sprite;

typedef struct s_sprite_calc
{
	double				sprite_x;
	double				sprite_y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					screen_x;
	int					sprite_height;
	int					sprite_width;
	int					draw_start_y;
	int					draw_end_y;
	int					draw_start_x;
	int					draw_end_x;
}						t_sprite_calc;

typedef struct s_texture_info
{
	char				*addr;
	int					bpp;
	int					line_len;
}						t_texture_info;

typedef struct s_render
{
	void				*texture_img;
	char				*texture_path;
	t_texture_info		info;
	int					texture_endian;
}						t_render;

typedef struct s_anim
{
	t_render			render_arr[MAX_ANIM_LENGTH];
	int					is_playing;
	unsigned int		index;
}						t_anim;

typedef struct s_sprite_bounds
{
	int					start_x;
	int					end_x;
	int					half_width;
	int					sprite_height;
	int					sprite_top;
}						t_sprite_bounds;

typedef struct s_sprite_params
{
	t_texture_info		*tex_info;
	int					x;
	int					tex_x;
	int					sprite_top;
	int					sprite_height;
}						t_sprite_params;

typedef struct s_enemy_render_data
{
	int					visible;
	int					screen_x;
	int					sprite_height;
	int					sprite_top;
	double				angle_diff;
}						t_enemy_render_data;

typedef struct s_mouse
{
	int					first_move;
	int					last_x;
	int					last_y;
	int					enabled;
	int					sensitivity;
}						t_mouse;

typedef struct s_enemy
{
	t_vector			position;
	t_render			render;
	t_enemy_render_data	enemy_data;
	int					health;
}						t_enemy;

typedef struct s_astar_node
{
	t_pos				pos;
	int					g_cost;
	int					h_cost;
	int					f_cost;
	struct s_astar_node	*parent;
	int					open;
	int					closed;
}						t_astar_node;

typedef struct s_astar_data
{
	t_astar_node		nodes[MAX_NODES];
	int					node_count;
	int					width;
	int					height;
}						t_astar_data;

typedef struct s_movement_data
{
	double				move_speed;
	t_pos				start;
	t_pos				goal;
	t_pos				path[128];
}						t_movement_data;

typedef struct s_data
{
	int					game_started;
	t_render			north_wall;
	t_render			south_wall;
	t_render			east_wall;
	t_render			west_wall;
	t_render			crosshair;
	t_render			door;
	t_anim				gun;
	t_anim				shot;
	t_color				floor;
	t_color				ceiling;
	void				*render_img;
	t_texture_info		render_info;
	int					render_endian;
	t_sprite			*sprites;
	int					sprite_count;
	int					config_lines;
	void				*mlx;
	void				*window;
	t_player			player;
	t_enemy				enemy;
	t_mouse				mouse;
	t_grid				grid;
	t_ray				rays[WINDOW_WIDTH];
	t_ray				shot_ray;
	t_keys				keys;
	int					render_fog;
	int					frame_count;
	double				fps;
	long long			last_time;
}						t_data;

typedef struct s_neighbor_context
{
	t_data				*data;
	t_astar_data		*astar;
	t_pos				goal;
	int					(*visited)[400];
}						t_neighbor_context;

// PARSING
int						parse_file(char *filename, t_data *data);
int						parse_map(char **all_lines, t_data *data);
int						parse_config_section(char **all_lines, t_data *data);
int						parse_texture_path(char **texture_ptr, char *path);
int						parse_color(char *color_str, t_color *color);
int						check_file_extension(char *filename);
int						validate_config(t_data *data);
int						find_player_pos(t_data *data);

// CHECKER
int						check_map(t_data *data);
int						is_map_surrounded(t_data *data);

// FUNCTIONS
// RAYCASTING/RENDERING FUNCTIONS
void					trace_ray(t_data *data, double angle);
void					render_walls(t_data *data);
void					init_walls(t_data *data);
void					clear_screen(t_data *data);
void					draw_floor(t_data *data, int x, int y);
void					put_pixel_to_image(t_data *data, int x, int y,
							int color);
int						get_wall_texture_pixel(t_data *data, int x, int y,
							int side);
void					update_player_movement(t_data *data);
t_wall_side				get_wall_side(t_data *data, int ray_index);
t_texture_info			get_texture_info_by_side(t_data *data,
							t_wall_side side);
void					apply_fog_overlay(t_data *data);
void					render_crosshair(t_data *data);
void					render_enemy(t_data *data);
void					update_enemy_movement(t_data *data);
int						find_astar_path(t_data *data, t_pos start, t_pos goal,
							t_pos *out_path);
void					update_player_stamina_status(t_data *data,
							double delta_time);
double					u_get_current_speed(t_data *data);
void					draw_sprite_at(t_data *data, t_render *render,
							t_sprite_bounds *bounds, t_enemy *enemy);
void					render_gun(t_data *data);
void					animation_routine(t_data *data);
void					trace_shot(t_data *data);

// RAYCASTING INIT FUNCTIONS
void					init_player_direction(t_data *data, double angle);
void					init_ray_direction(t_data *data, int i);
void					init_ray_distances(t_data *data, int i);
void					init_ray_steps(t_data *data, int i);
void					init_mouse_control(t_data *data);
int						mouse_move(int x, int y, void *param);
void					toggle_mouse_control(t_data *data);

// UTILS
int						u_rgb_to_hex(int r, int g, int b, int a);
int						u_is_empty_line(char *line);
int						u_is_config_line(char *line);
void					u_calculate_map_width(t_data *data);
void					u_ft_free(char **res);
int						close_window(t_data *data);
void					u_print_error(char *msg);
int						u_is_empty_line(char *line);
int						u_is_config_line(char *line);
void					u_calculate_map_width(t_data *data);
void					u_ft_free(char **res);
long long				get_current_time(void);
void					calculate_fps(t_data *data);
void					extract_base_colors(int base_color, int *r, int *g,
							int *b);
void					extract_fog_colors(int fog_color, int *r, int *g,
							int *b);
int						calculate_fog_alpha(double distance);
int						get_pixel_from_image(t_data *data, int x, int y);
unsigned int			get_texture_pixel(t_texture_info *texture_info, int x,
							int y);
int						blend_colors(t_color *colors, double alpha);
int						is_out_of_bounds(int x, int y, int height, int width);
int						is_valid_map_char(char c);
void					load_texture(t_data *data, char *path,
							t_render *texture);
void					init(t_data *data, char **argv);
int						check_collisions(t_data *data, t_vector move);
void					handle_forward_backward(t_data *data, t_vector *move,
							double move_speed);
void					handle_strafe(t_data *data, t_vector *move,
							double move_speed);
void					normalize_movement(t_data *data, t_vector *move,
							double *magnitude, double move_speed);
int						check_wall_occlusion(t_data *data, int x,
							t_enemy *enemy);
void					calculate_sprite_bounds(int screen_x, int sprite_height,
							t_sprite_bounds *bounds);
void					draw_sprite_column(t_data *data,
							t_sprite_params *params);
t_sprite_params			init_sprite_params(t_texture_info *info, int spr_top,
							int spr_height);
void					add_neighbor(t_neighbor_context *ctx,
							t_astar_node *curr, int nx, int ny);
int						is_valid_neighbor(t_data *data, t_astar_data *astar,
							int nx, int ny);
int						reconstruct_path(t_astar_node *goal_node,
							t_pos *out_path, int max_len);
int						find_lowest_f_cost(t_astar_data *astar);
void					init_astar_data(t_data *data, t_astar_data *astar,
							t_pos start, t_pos goal);
int						is_valid_position(t_data *data, double x, double y);
int						heuristic(t_pos a, t_pos b);
int						calc_horizon_line(t_data *data);
void					check_door_distance(t_data *data, int keycode);
int						is_transparent_color(unsigned int color);
void					init_ray_direction_shot(t_data *data);
void					init_ray_distances_shot(t_data *data);
void					init_ray_steps_shot(t_data *data);

#endif