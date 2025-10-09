/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:19:42 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/09 15:19:53 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square(t_data *data, int x, int y, int color, int scale)
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

void	draw_minimap_player_with_direction(t_data *data, int start_x,
	int start_y, int cell_size)
{
	int	player_pixel_x;
	int	player_pixel_y;
	int	offset;

	player_pixel_x = start_x + (int)(data->player.position.x * cell_size);
	player_pixel_y = start_y + (int)(data->player.position.y * cell_size);
	offset = cell_size / 4;
	draw_square(data, player_pixel_x - offset, player_pixel_y - offset,
		0xFF0000, cell_size / 2);
	draw_minimap_fov_cone(data, start_x, start_y, cell_size);
}

void	draw_minimap_fov_cone(t_data *data, int start_x,
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

static int	check_ray_bounds(t_data *data, int grid_x, int grid_y)
{
	if (grid_y < 0 || grid_y >= data->grid.height
		|| grid_x < 0 || grid_x >= data->grid.width)
		return (1);
	if (data->grid.grid[grid_y][grid_x] == '1'
		|| data->grid.grid[grid_y][grid_x] == '2')
		return (1);
	return (0);
}

void	draw_ray_on_minimap(t_data *data, int start_x, int start_y,
	int cell_size, double angle, int color)
{
	t_ray_params	ray;
	int				pixel_x;
	int				pixel_y;

	ray.x = data->player.position.x;
	ray.y = data->player.position.y;
	ray.step = 0.1 + (cell_size / 100.0);
	ray.i = 0;
	while (++ray.i < 100)
	{
		ray.grid_x = (int)ray.x;
		ray.grid_y = (int)ray.y;
		if (check_ray_bounds(data, ray.grid_x, ray.grid_y))
			break ;
		pixel_x = start_x + (int)(ray.x * cell_size);
		pixel_y = start_y + (int)(ray.y * cell_size);
		put_pixel_to_image(data, pixel_x, pixel_y, color);
		ray.x += cos(angle) * ray.step;
		ray.y += sin(angle) * ray.step;
	}
}
