/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:01:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/11/26 16:56:07 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

// FUNCTIONS
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
int					check_map(t_data *data);
int					is_map_surrounded(t_data *data);
void				validate_window_size(void);
int					check_map_content(char *all_lines);
int					map_start_buff(char *all_lines);
int					check_settings(void);
int					check_comas(char *trimmed);

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
void				render_crosshair(t_data *data);

// RAYCASTING INIT FUNCTIONS
void				init_player_direction(t_data *data, double angle);
void				init_ray_direction(t_data *data, int i);
void				init_ray_distances(t_data *data, int i);
void				init_ray_steps(t_data *data, int i);
void				init_mouse_control(t_data *data);
int					mouse_move(int x, int y, void *param);
void				toggle_mouse_control(t_data *data);

// UTILS
int					u_rgb_to_hex(int r, int g, int b, int a);
int					u_is_empty_line(char *line);
int					u_is_config_line(char *line);
void				u_calculate_map_width(t_data *data);
void				u_ft_free(char **res);
int					close_window(t_data *data);
void				u_print_error(char *msg);
int					u_is_empty_line(char *line);
int					skip_whitespace(char *all_lines, int i);
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
int					is_out_of_bounds(int x, int y, int height, int width);
int					is_valid_map_char(char c);
void				load_texture(t_data *data, char *path, t_render *texture);
void				init(t_data *data, char **argv);
int					ft_atoi_n_check(const char *nptr);
void				free_grid_partial(t_data *data, int count);

#endif
