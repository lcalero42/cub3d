/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_rendering_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalero <lcalero@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:25:57 by lcalero           #+#    #+#             */
/*   Updated: 2025/09/02 19:18:38 by lcalero          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	calc_floor_color(t_data *data, char color, float t);

void	draw_floor(t_data *data, int start_x, int y)
{
	float	t;
	int		adjusted_horizon;
	int		x;
	int		floor_height;

	adjusted_horizon = calc_horizon_line(data);
	floor_height = WINDOW_HEIGHT - adjusted_horizon;
	if (floor_height <= 0)
		floor_height = 1;
	t = (float)(y - adjusted_horizon) / (float)floor_height;
	if (t > 1.0f)
		t = 1.0f;
	if (t < 0.0f)
		t = 0.0f;
	x = start_x;
	while (x < WINDOW_WIDTH)
	{
		put_pixel_to_image(data, x, y, u_rgb_to_hex(calc_floor_color(data, 'r',
					t), calc_floor_color(data, 'g', t), calc_floor_color(data,
					'b', t), 0));
		x++;
	}
}

int	get_pixel_from_image(t_data *data, int x, int y)
{
	char	*pixel_addr;
	int		color;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return (0);
	pixel_addr = data->render_info.addr + y * data->render_info.line_len + x
		* (data->render_info.bpp / 8);
	color = *(unsigned int *)pixel_addr;
	return (color);
}

int	blend_colors(t_color *colors, double alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(colors->base_r * (1.0 - alpha) + colors->fog_r * alpha);
	g = (int)(colors->base_g * (1.0 - alpha) + colors->fog_g * alpha);
	b = (int)(colors->base_b * (1.0 - alpha) + colors->fog_b * alpha);
	return ((r << 16) | (g << 8) | b);
}

void	extract_base_colors(int base_color, int *r, int *g, int *b)
{
	*r = (base_color >> 16) & 0xFF;
	*g = (base_color >> 8) & 0xFF;
	*b = base_color & 0xFF;
}

static int	calc_floor_color(t_data *data, char color, float t)
{
	int	floor_r;
	int	floor_g;
	int	floor_b;

	if (data->render_fog)
	{
		floor_r = (int)(data->floor.base_r * (0.3f + 0.7f * t));
		floor_g = (int)(data->floor.base_g * (0.3f + 0.7f * t));
		floor_b = (int)(data->floor.base_b * (0.3f + 0.7f * t));
	}
	else
	{
		floor_r = data->floor.base_r;
		floor_g = data->floor.base_g;
		floor_b = data->floor.base_b;
	}
	if (color == 'r')
		return (floor_r);
	else if (color == 'g')
		return (floor_g);
	else
		return (floor_b);
}
