/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:18:22 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/18 18:05:26 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_BONUS_H
# define FUNCTIONS_BONUS_H

# include "structures_bonus.h"

/* PARSING */
int				parse_file(char *filename, t_data *data);
int				parse_map(char **all_lines, t_data *data);
int				parse_config_section(char **all_lines, t_data *data);
int				parse_texture_path(char **texture_ptr, char *path);
int				parse_color(char *color_str, t_color *color);
int				check_file_extension(char *filename);
int				validate_config(t_data *data);
int				find_player_pos(t_data *data);

/* CHECKER */
int				check_map(t_data *data);
int				check_map_content(char *all_lines);
int				is_map_surrounded(t_data *data);
void			validate_window_size(void);
void			check_enemy_can_spawn(t_data *data);
int				map_start_buff(char *all_lines);

/* RAYCASTING/RENDERING */
void			trace_ray(t_data *data, double angle);
void			perform_dda(t_data *data, int i);
void			perform_dda_step(t_data *data, int i);
void			render_walls(t_data *data);
void			init_walls(t_data *data);
void			clear_screen(t_data *data);
void			put_pixel_to_image(t_data *data, int x, int y, int color);
int				get_wall_texture_pixel(t_data *data, int y,
					int ray_index, int index_hit);
void			update_player_movement(t_data *data);
t_wall_side		get_wall_side(t_data *data, int ray_index);
t_texture_info	get_texture_info_by_side(t_data *data, t_wall_side side);
void			render_crosshair(t_data *data);
void			render_gun(t_data *data);
void			animation_routine(t_data *data);
void			trace_shot(t_data *data);
void			toggle_door(t_door *door);
void			init_health_pad_system(t_data *data);
void			check_health_pickup_collision(t_data *data);
void			check_door_interaction(t_data *data, int keycode);
int				calculate_texture_x_for_hit(t_data *data,
					int ray_index, int hit_index);
int				collect_all_sprites(t_data *data, t_generic_sprite *sprites);
void			sort_sprites_by_distance(t_generic_sprite *sprites, int count);
void			calculate_sprite_position(t_data *data,
					t_generic_sprite *sprite);
void			calculate_sprite_size(t_generic_sprite *sprite);
void			calculate_sprite_bounds_y(t_data *data, t_sprite_calc *calc);
void			calculate_sprite_bounds_x(t_sprite_calc *calc);
double			calculate_sprite_distance(t_vector sprite_pos,
					t_player *player);
void			calculate_sprite_bounds_from_calc(t_sprite_calc *calc,
					int *sprite_top, int *sprite_bottom);
int				check_door_occlusion_at_ray(t_data *data, int x,
					int i, int sprite_bounds[2]);
int				check_hit_occlusion(t_data *data, int x,
					int i, t_occlusion_data *occ_data);
int				check_hit_occlusion(t_data *data, int x,
					int i, t_occlusion_data *occ_data);

/* RAYCASTING INIT */
void			init_player_direction(t_data *data, double angle);
void			init_ray_direction(t_data *data, int i);
void			init_ray_distances(t_data *data, int i);
void			init_ray_steps(t_data *data, int i);
void			init_mouse_control(t_data *data);
int				mouse_move(int x, int y, void *param);
void			apply_rotation_with_limits(t_data *data,
					int smooth_x, int smooth_y);
void			update_player_direction(t_data *data);
void			handle_recenter(t_data *data, int force);
void			mouse_rotation(int delta_x, int delta_y, t_data *data);
void			add_to_smooth_buffer(t_data *data, int delta_x, int delta_y);
void			get_smoothed_delta(t_data *data, int *smooth_x, int *smooth_y);
int				handle_first_move(t_data *data);
int				check_out_of_bounds(int x, int y, t_data *data);
int				handle_first_move(t_data *data);
void			norm_angle(double *angle, t_data *data);
void			clamp_delta(int *delta_x, int *delta_y, double magnitude);
void			toggle_mouse_control(t_data *data);
void			reset_game(t_data *data);
void			spawn_enemy(t_data *data);

/* ENEMY & AI */
void			update_enemy_movement(t_data *data);
int				find_astar_path(t_data *data, t_pos start, t_pos goal,
					t_pos *out_path);
void			render_enemy_with_health(t_data *data, t_enemy *enemy);
int				ray_hits_enemy(t_data *data);

/* HEALTH & UI */
void			render_health_bar(t_data *data, t_health_bar *health_bar);
void			render_stamina(t_data *data, t_health_bar *bar);
void			init_health_bar(t_health_bar *health_bar, t_data *data);
unsigned int	get_health_color(t_data *data);
void			draw_health_bar_background(t_data *data,
					t_health_bar *health_bar);
void			render_minimap(t_data *data);
void			draw_square(t_data *data, t_square_params params);
void			draw_minimap_player_with_direction(t_data *data,
					t_minimap_params *params);
void			draw_minimap_fov_cone(t_data *data, t_minimap_params *params);
void			draw_ray_on_minimap(t_data *data, t_ray_draw_params *params);
void			init_ray_params(t_minimap_params *params,
					t_ray_draw_params *ray);
void			render_menu(t_data *data);
int				handle_menu_button_clicks(t_data *data,
					int mouse_x, int mouse_y);
void			calculate_sprite_transform(t_data *data,
					t_generic_sprite *sprite);
void			render_sprite(t_data *data, t_generic_sprite *sprite);
void			render_health_pad_sprite(t_data *data, t_health_pad *pad,
					t_sprite_calc *calc);
int				check_sprite_occlusion(t_data *data, int x, t_vector sprite_pos,
					t_sprite_calc *calc);
int				check_enemy_occlusion(t_data *data, int x, t_enemy *enemy);
void			draw_button_at(t_data *data, t_render *render,
					t_sprite_bounds *bounds);
void			render_game_over_screen(t_data *data);
void			render_background(t_data *data);
int				handle_scene(t_data *data);

/* PLAYER & MOVEMENT */
void			update_player_stamina_status(t_data *data);
double			u_get_current_speed(t_data *data);
int				check_collisions(t_data *data, t_vector move);
void			handle_forward_backward(t_data *data, t_vector *move,
					double move_speed);
void			handle_strafe(t_data *data, t_vector *move, double move_speed);
void			normalize_movement(t_data *data, t_vector *move,
					double *magnitude, double move_speed);

/* INPUT HANDLING */
void			handle_move_keys(t_data *data, int keycode);
int				key_release_hook(int keycode, t_data *data);
int				key_press_hook(int keycode, t_data *data);
int				mouse_hook(int keycode, int x, int y, t_data *data);

/* SPRITE RENDERING */
int				check_enemy_occlusion(t_data *data, int x, t_enemy *enemy);
void			calculate_sprite_bounds(int screen_x, int sprite_height,
					t_sprite_bounds *bounds);
void			draw_sprite_column(t_data *data, t_sprite_params *params,
					t_sprite_bounds *bounds);
t_sprite_params	init_sprite_params(t_texture_info *info, int spr_top,
					int spr_height);
void			render_all_sprites(t_data *data);
void			render_health_pad_sprite(t_data *data, t_health_pad *pad,
					t_sprite_calc *calc);

/* ASTAR PATHFINDING */
void			add_neighbor(t_neighbor_context *ctx, t_astar_node *curr,
					int nx, int ny);
int				is_valid_neighbor(t_data *data, t_astar_data *astar,
					int nx, int ny);
int				reconstruct_path(t_astar_node *goal_node, t_pos *out_path,
					int max_len);
int				find_lowest_f_cost(t_astar_data *astar);
void			init_astar_data(t_data *data, t_astar_data *astar,
					t_pos start, t_pos goal);
int				is_valid_position(t_data *data, double x, double y);
int				heuristic(t_pos a, t_pos b);

/* SHOOTING */
void			init_ray_direction_shot(t_data *data);
void			init_ray_distances_shot(t_data *data);
void			init_ray_steps_shot(t_data *data);

/* UTILS */
int				u_rgb_to_hex(int r, int g, int b, int a);
int				u_is_empty_line(char *line);
int				u_is_config_line(char *line);
void			u_calculate_map_width(t_data *data);
void			u_ft_free(char **res);
int				skip_whitespace(char *all_lines, int i);
void			u_ft_free_doors(t_data *data);
int				close_window(t_data *data);
void			u_print_error(char *msg);
long long		get_current_time(void);
void			calculate_fps(t_data *data);
int				get_pixel_from_image(t_data *data, int x, int y);
int				is_out_of_bounds(int x, int y, int height, int width);
int				is_valid_map_char(char c);
void			load_texture(t_data *data, char *path, t_render *texture);
void			init(t_data *data, char **argv);
t_texture_info	get_door_texture(t_data *data, t_door *door);
void			init_door_system(t_data *data);
int				is_transparent_color(unsigned int color);
int				get_door_pixel_at_position(t_data *data, int x,
					int y, int hit_index);
t_wall_side		get_wall_side_from_stored(int stored_side,
					t_data *data, int ray_index);
void			calc_delta_time_ms(t_data *data);
int				check_sprite_occlusion(t_data *data, int x, t_vector sprite_pos,
					t_sprite_calc *calc);
int				is_door_pos_valid(t_data *data, t_pos door_pos);
int				sample_door_pixels(t_data *data, int x, int i,
					int sprite_bounds[2]);
int				add_enemy_sprite(t_data *data, t_generic_sprite *sprites);
void			add_health_pad_sprite(t_data *data, t_generic_sprite *sprites,
					int *count, int i);
int				is_valid_spawn(t_data *data, int x, int y);
int				ft_atoi_n_check(const char *nptr);
void			free_paths(t_data *data);

/* COLOR & FOG */
void			extract_base_colors(int base_color, int *r, int *g, int *b);
void			extract_fog_colors(int fog_color, int *r, int *g, int *b);
int				calculate_fog_alpha(double distance);
int				blend_colors(t_color *colors, double alpha);
int				blend_fog_with_pixel(int base_color, int fog_color,
					int fog_alpha);
int				calculate_ground_fog_alpha(int y, int horizon_line);
void			draw_sky_line_with_fog(t_data *data, int y, int horizon_line);

/* ENEMY RENDERING */
void			calculate_health_bar_position(t_enemy_render_data *r_dt,
					t_enemy_health_bar *health_bar);
void			calculate_enemy_screen_pos(t_enemy *enemy, t_player *player,
					t_enemy_render_data *render_data, t_data *data);

#endif