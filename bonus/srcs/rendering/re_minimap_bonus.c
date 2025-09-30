/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:45:42 by ekeisler          #+#    #+#             */
/*   Updated: 2025/09/30 19:48:14 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void draw_square(t_data *data, int x, int y, int color, int scale);
static void draw_minimap_player_with_direction(t_data *data, int start_x, int start_y, int cell_size);
static void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);

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
	start_x = WINDOW_WIDTH - minimap_size;
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
			draw_minimap_player_with_direction(data, start_x, start_y, cell_size);
			j++;
		}
		i++;
	}
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

static void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
	
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx - dy;
	x = x0;
	y = y0;
	while (1)
	{
		put_pixel_to_image(data, x, y, color);
		if (x == x1 && y == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

static void draw_minimap_player_with_direction(t_data *data, int start_x, int start_y, int cell_size)
{
	int player_pixel_x;
	int	player_pixel_y;
	int dir_end_x;
	int	dir_end_y;

	player_pixel_x = start_x + (int)(data->player.position.x * cell_size);
	player_pixel_y = start_y + (int)(data->player.position.y * cell_size);
	draw_square(data, player_pixel_x - cell_size/4, player_pixel_y - cell_size/4, 
			   0xFF0000, cell_size/2);
	dir_end_x = player_pixel_x + (int)(data->player.dir.x * cell_size);
	dir_end_y = player_pixel_y + (int)(data->player.dir.y * cell_size);
	draw_line(data, player_pixel_x, player_pixel_y, dir_end_x, dir_end_y, 0xFF0000);
}