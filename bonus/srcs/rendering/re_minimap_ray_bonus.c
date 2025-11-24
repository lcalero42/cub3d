/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_ray_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:32:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/11/24 16:57:22 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_ray_bounds(t_data *data, int grid_x, int grid_y);

void	draw_ray_on_minimap(t_data *data, t_ray_draw_params *params)
{
	t_ray_state	ray;
	int			pixel_x;
	int			pixel_y;

	ray.x = data->player.position.x;
	ray.y = data->player.position.y;
	ray.step = 0.1 + (params->cell_size / 100.0);
	ray.i = 0;
	while (++ray.i < 100)
	{
		ray.grid_x = (int)ray.x;
		ray.grid_y = (int)ray.y;
		if (check_ray_bounds(data, ray.grid_x, ray.grid_y))
			break ;
		pixel_x = params->start_x + (int)(ray.x * params->cell_size);
		pixel_y = params->start_y + (int)(ray.y * params->cell_size);
		put_pixel_to_image(data, pixel_x, pixel_y, params->color);
		ray.x += cos(params->angle) * ray.step;
		ray.y += sin(params->angle) * ray.step;
	}
}

static int	check_ray_bounds(t_data *data, int grid_x, int grid_y)
{
	if (grid_y < 0 || grid_y >= data->grid.height)
		return (1);
	if (grid_x < 0 || grid_x >= (int)ft_strlen(data->grid.grid[grid_y]))
		return (1);
	if (data->grid.grid[grid_y][grid_x] == '1'
		|| data->grid.grid[grid_y][grid_x] == '2')
		return (1);
	return (0);
}
