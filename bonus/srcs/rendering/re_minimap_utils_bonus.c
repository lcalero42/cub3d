/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_minimap_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeisler <ekeisler@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:18:00 by ekeisler          #+#    #+#             */
/*   Updated: 2025/10/09 15:32:48 by ekeisler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square(t_data *data, t_square_params params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params.scale)
	{
		j = 0;
		while (j < params.scale)
		{
			put_pixel_to_image(data, params.x + j, params.y + i,
				params.color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player_with_direction(t_data *data,
	t_minimap_params *params)
{
	int				player_pixel_x;
	int				player_pixel_y;
	int				offset;
	t_square_params	square;

	player_pixel_x = params->start_x
		+ (int)(data->player.position.x * params->cell_size);
	player_pixel_y = params->start_y
		+ (int)(data->player.position.y * params->cell_size);
	offset = params->cell_size / 4;
	square.x = player_pixel_x - offset;
	square.y = player_pixel_y - offset;
	square.color = 0xFF0000;
	square.scale = params->cell_size / 2;
	draw_square(data, square);
	draw_minimap_fov_cone(data, params);
}

void	init_ray_params(t_minimap_params *params, t_ray_draw_params *ray)
{
	ray->start_x = params->start_x;
	ray->start_y = params->start_y;
	ray->cell_size = params->cell_size;
	ray->color = 0xFF0000;
}

void	draw_minimap_fov_cone(t_data *data, t_minimap_params *params)
{
	t_fov_cone_params	fov;
	t_ray_draw_params	ray_params;
	int					i;

	fov.fov = M_PI / 3;
	fov.rays = 20;
	fov.start_angle = data->player.angle - fov.fov / 2;
	fov.end_angle = data->player.angle + fov.fov / 2;
	init_ray_params(params, &ray_params);
	i = 0;
	while (i <= fov.rays)
	{
		ray_params.angle = fov.start_angle + (fov.end_angle - fov.start_angle)
			* ((double)i / (double)fov.rays);
		draw_ray_on_minimap(data, &ray_params);
		i++;
	}
}
