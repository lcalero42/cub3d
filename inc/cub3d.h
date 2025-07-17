/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:01:03 by lcalero           #+#    #+#             */
/*   Updated: 2025/07/16 02:44:58 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# ifndef WINDOW_WIDTH
 # define WINDOW_WIDTH 640
# endif
# ifndef WINDOW_HEIGHT
 # define WINDOW_HEIGHT 480
# endif
# define FOV (60.0 * M_PI / 180.0)

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_ray
{
	t_vector ray_dir;         // direction du rayon
	t_vector map_pos;         // position du joueur dans la grille (en int)
	t_vector side_dist;       // distance au prochain X/Y
	t_vector delta_dist;      // distance entre deux intersections X/Y
	t_vector step;            // direction à incrémenter dans la grille (+1 ou -1)
	int hit;
	int side;              // 0 = côté X, 1 = côté Y

} t_ray;

typedef struct s_grid
{
	char	**grid;
	int		width;
	int		height;
} t_grid;

typedef struct s_player 
{
	t_vector	position;
	t_vector	camera_segment;
	t_vector	dir;
	double		fov;
} t_player;

typedef struct s_color 
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_path
{
	char *north;
	char *west;
	char *south;
	char *east;
} t_path;

typedef struct s_config {
    t_path		path;
    t_color     floor;
    t_color     ceiling;
	t_grid		map;
    int         config_lines;
} t_config;

// typedef struct s_camera 
// {
// 	float x_position;
// 	float y_position;
// } t_camera;

typedef struct s_data 
{
	void		*mlx;
	void		*window;
	t_player	player;
	t_grid		grid;
	t_ray		rays[WINDOW_WIDTH];
} t_data;

// parsing
int		parse_file(char *filename, t_config *config);
int		parse_config_section(char **all_lines, t_config *config);
int		parse_map(char **all_lines, t_config *config);
void 	init_config(t_config *config);
// raycasting
void	trace_ray(t_data *data, double angle);

// utils
int		u_is_empty_line(char *line);
int		u_is_config_line(char *line);
void	u_calculate_map_width(t_config *config);
#endif