/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_fog_rendering_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:23:43 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/16 17:51:03 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	calculate_sky_fog_alpha(int y, int horizon_line);

int	calculate_fog_alpha(double distance)
{
	double	ratio;

	if (distance <= FOG_START_DISTANCE)
		return (0);
	if (distance >= FOG_END_DISTANCE)
		return (FOG_MAX_ALPHA);
	ratio = (distance - FOG_START_DISTANCE)
		/ (FOG_END_DISTANCE - FOG_START_DISTANCE);
	return ((int)(ratio * FOG_MAX_ALPHA));
}

void	extract_fog_colors(int fog_color, int *r, int *g, int *b)
{
	*r = (fog_color >> 16) & 0xFF;
	*g = (fog_color >> 8) & 0xFF;
	*b = fog_color & 0xFF;
}

int	calculate_ground_fog_alpha(int y, int horizon_line)
{
	double	distance_ratio;
	double	fog_intensity;
	int		fog_alpha;

	if (y <= horizon_line)
		return (0);
	if (WINDOW_HEIGHT - horizon_line <= 0)
		return (0);
	distance_ratio = (double)(y - horizon_line)
		/ (WINDOW_HEIGHT - horizon_line);
	fog_intensity = (1.0 - distance_ratio) * 0.8;
	fog_alpha = (int)(fog_intensity * FOG_MAX_ALPHA);
	if (fog_alpha > FOG_MAX_ALPHA)
		fog_alpha = FOG_MAX_ALPHA;
	return (fog_alpha);
}

void	draw_sky_line_with_fog(t_data *data, int y, int horizon_line)
{
	int	x;
	int	fog_alpha;
	int	base_color;
	int	fog_color;
	int	final_color;

	fog_alpha = calculate_sky_fog_alpha(y, horizon_line);
	base_color = u_rgb_to_hex(data->ceiling.base_r, data->ceiling.base_g,
			data->ceiling.base_b, 255);
	fog_color = u_rgb_to_hex(FOG_COLOR_R, FOG_COLOR_G, FOG_COLOR_B, 255);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		if (fog_alpha > 0)
			final_color = blend_fog_with_pixel(base_color,
					fog_color, fog_alpha);
		else
			final_color = base_color;
		put_pixel_to_image(data, x, y, final_color);
		x++;
	}
}

static int	calculate_sky_fog_alpha(int y, int horizon_line)
{
	double	distance_ratio;
	double	fog_intensity;
	int		fog_alpha;

	if (y >= horizon_line || horizon_line <= 0)
		return (0);
	distance_ratio = (double)(horizon_line - y) / horizon_line;
	fog_intensity = distance_ratio * distance_ratio * 0.7;
	fog_alpha = (int)(fog_intensity * FOG_MAX_ALPHA);
	if (fog_alpha > FOG_MAX_ALPHA)
		fog_alpha = FOG_MAX_ALPHA;
	return (fog_alpha);
}
