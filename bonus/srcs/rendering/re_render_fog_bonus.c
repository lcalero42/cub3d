/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_fog_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:09:27 by lcalero           #+#    #+#             */
/*   Updated: 2025/08/27 17:57:04 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	blend_fog_with_pixel(int base_color, int fog_color, int fog_alpha)
{
	t_color			colors;
	double			alpha_factor;

	extract_base_colors(base_color, &colors.base_r, &colors.base_g,
		&colors.base_b);
	extract_fog_colors(fog_color, &colors.fog_r, &colors.fog_g,
		&colors.fog_b);
	alpha_factor = fog_alpha / 255.0;
	return (blend_colors(&colors, alpha_factor));
}

static void	apply_fog_column(t_data *data, t_fog_params *params)
{
	int	y;
	int	existing_color;
	int	blended_color;

	y = params->wall_start;
	while (y < params->wall_end)
	{
		existing_color = get_pixel_from_image(data, params->x, y);
		blended_color = blend_fog_with_pixel(existing_color,
				params->fog_color, params->fog_alpha);
		put_pixel_to_image(data, params->x, y, blended_color);
		y++;
	}
}

static void	calculate_wall_bounds(double distance, t_wall_bounds *bounds)
{
	int	wall_height;

	wall_height = (int)(WINDOW_HEIGHT / distance);
	bounds->wall_start = (WINDOW_HEIGHT - wall_height) / 2;
	bounds->wall_end = bounds->wall_start + wall_height;
}

static void	process_fog_column(t_data *data, int x)
{
	t_ray			*ray;
	t_fog_params	params;
	t_wall_bounds	bounds;

	ray = &data->rays[x];
	params.fog_alpha = calculate_fog_alpha(ray->perp_wall_dist);
	if (params.fog_alpha > 0)
	{
		calculate_wall_bounds(ray->perp_wall_dist, &bounds);
		params.x = x;
		params.wall_start = bounds.wall_start;
		params.wall_end = bounds.wall_end;
		params.fog_color = u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G,
				FOG_COLOR_B, 255);
		apply_fog_column(data, &params);
	}
}

void	apply_fog_overlay(t_data *data)
{
	int	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		process_fog_column(data, x);
		x++;
	}
}
