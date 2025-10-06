/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:45:42 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/06 18:19:18 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_square(t_data *data, int x, int y, int color, int scale);
static void	draw_minimap_player_with_direction(t_data *data, int start_x,
				int start_y, int cell_size);
static void draw_ray_on_minimap(t_data *data, int start_x, int start_y, int cell_size, double angle, int color);
static void draw_minimap_fov_cone(t_data *data, int start_x, int start_y, int cell_size);

void	render_minimap(t_data *data)
{
	int	minimap_size;
	int	minimap_margin;
	int	cell_size;
	int	start_x;
	int	start_y;
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;

	cell_size = WINDOW_WIDTH / 120;
	if (cell_size < 5)
		cell_size = 5;
	if (cell_size > 16)
		cell_size = 16;
	minimap_margin = WINDOW_WIDTH * 0.05;
	minimap_size = fmax(data->grid.width, data->grid.height) * cell_size;
	start_x = WINDOW_WIDTH - minimap_size * 1.05;
	start_y = minimap_margin;
	i = 0;
	while (data->grid.grid[i])
	{
		j = 0;
		while (data->grid.grid[i][j])
		{
			pixel_x = start_x + j * cell_size;
			pixel_y = start_y + i * cell_size;
			if (data->grid.grid[i][j] != ' ')
				draw_square(data, pixel_x, pixel_y, 0xFFFFFF, cell_size);
			if (data->grid.grid[i][j] == '1')
				draw_square(data, pixel_x, pixel_y, 0x000000, cell_size);
			if (data->grid.grid[i][j] == '2')
				draw_square(data, pixel_x, pixel_y, 0x8B4513, cell_size);
			j++;
			}
			i++;
		}
		draw_minimap_player_with_direction(data, start_x,
			start_y, cell_size);
}

static void	draw_square(t_data *data, int x, int y, int color, int scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel_to_image(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_player_with_direction(t_data *data, int start_x,
				int start_y, int cell_size)
{
	int	player_pixel_x;
	int	player_pixel_y;
	int	dir_end_x;
	int	dir_end_y;

	player_pixel_x = start_x + (int)(data->player.position.x * cell_size);
	player_pixel_y = start_y + (int)(data->player.position.y * cell_size);
	draw_square(data, player_pixel_x - cell_size/4,
		player_pixel_y - cell_size/4, 0xFF0000, cell_size/2);
	dir_end_x = player_pixel_x + (int)(data->player.dir.x * cell_size);
	dir_end_y = player_pixel_y + (int)(data->player.dir.y * cell_size);
	draw_minimap_fov_cone(data, start_x, start_y, cell_size);
}

static void	draw_minimap_fov_cone(t_data *data, int start_x, 
	int start_y, int cell_size)
{
	double	fov;
	int		rays;
	double	start_angle;
	double	end_angle;
	int		i;

	fov = M_PI / 3;
	rays = 20;
	start_angle = data->player.angle - fov / 2;
	end_angle = data->player.angle + fov / 2;
	i = 0;
	while (i <= rays)
	{
		draw_ray_on_minimap(data, start_x, start_y, cell_size,
			start_angle + (end_angle - start_angle) 
			* ((double)i / (double)rays), 0xFF0000);
		i++;
	}
}


static void draw_ray_on_minimap(t_data *data, int start_x, int start_y,
	int cell_size, double angle, int color)
{
	double	ray_x;
	double	ray_y;
	double	step;
	int		max_steps;
	int		grid_x;
	int		grid_y;
	int		pixel_x;
	int		pixel_y;
	int		i;

	ray_x = data->player.position.x;
	ray_y = data->player.position.y;
	step = 0.1 + (cell_size / 100.0);
	max_steps = 100;
	i = 0;
	while (++i < max_steps)
	{
		grid_x = (int)ray_x;
		grid_y = (int)ray_y;
		if (grid_y < 0 || grid_y >= data->grid.height
			|| grid_x < 0 || grid_x >= data->grid.width)
			break ;
		if (data->grid.grid[grid_y][grid_x] == '1'
			|| data->grid.grid[grid_y][grid_x] == '2')
			break ;
		pixel_x = start_x + (int)(ray_x * cell_size);
		pixel_y = start_y + (int)(ray_y * cell_size);
		put_pixel_to_image(data, pixel_x, pixel_y, color);
		ray_x += cos(angle) * step;
		ray_y += sin(angle) * step;
	}
}

